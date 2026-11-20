#!/usr/bin/env python3
"""Generate reference-title source permalinks from a matching Doxygen XML build.

Build the guide from the intended source revision first, then pass its full Git
commit ID with --revision. This script does not invoke Git or contact GitHub.
"""

import argparse
from pathlib import Path
import re
from urllib.parse import quote
import xml.etree.ElementTree as ET


def normalize(name):
    return re.sub(r"\s+", "", name)


def load_symbols(xml_dir):
    symbols = {}
    classes = {}
    index = ET.parse(xml_dir / "index.xml")
    for entry in index.findall("compound"):
        if entry.get("kind") not in ("class", "struct", "concept", "namespace", "file"):
            continue
        compound = ET.parse(xml_dir / (entry.get("refid") + ".xml")).find("compounddef")
        name = compound.findtext("compoundname", "")
        location = compound.find("location")
        if entry.get("kind") in ("class", "struct") and location is not None:
            classes[normalize(name)] = (compound, location)
        if entry.get("kind") in ("class", "struct", "concept") and location is not None:
            symbols.setdefault(normalize(name), []).append(location)
        for member in compound.findall("sectiondef/memberdef"):
            location = member.find("location")
            if location is None:
                continue
            qualified = member.findtext("qualifiedname")
            if qualified is None:
                if entry.get("kind") == "file":
                    continue
                qualified = name + "::" + member.findtext("name", "")
            symbols.setdefault(normalize(qualified), []).append(location)
    return symbols, classes


def source_target(title, text, symbols, classes):
    header = re.search(r"Header:?\s+`?<([^>]+)>`?", title)
    if header:
        return "include/" + header[1], None, "header"
    header = re.search(r"Header: \[`<([^>]+)>`\]", text)
    if header is None:
        return None  # Topic pages do not have a declaration to link.
    header_path = "include/" + header[1]
    if title == "SGR and ANSI helpers":
        return None
    # Collections do not have a single declaration. Use their common header.
    if ("specializations" in title or "for colors" in title
            or title.startswith("`std::formatter::")):
        return header_path, None, "collection"
    if title.startswith("Named `tjg::color::rgb`"):
        return header_path, None, "collection"
    # Friend operators are documented with the associated class in the title.
    friend = re.fullmatch(r"`([^`]+)` for `([^`]+)`", title)
    if friend:
        parent = classes.get(normalize(friend[2]))
        if parent is None:
            raise ValueError(f"No enclosing class for {title}")
        members = [m.find("location") for m in parent[0].findall("sectiondef/memberdef")
                   if normalize(m.findtext("name", "")) == normalize(friend[1])]
        locations = [location for location in members if location is not None]
        if locations:
            location = min(locations, key=lambda loc: int(loc.get("line", "1")))
            return location.get("file"), int(location.get("line", "1")), "declaration"
        return parent[1].get("file"), int(parent[1].get("line", "1")), "enclosing class"
    entity = re.fullmatch(r"`([^`]+)`", title)
    if entity is None:
        raise ValueError(f"Unrecognized declaration title: {title}")
    name = normalize(entity[1])
    locations = symbols.get(name, [])
    # Four implementation helpers have retained pages after moving into detail.
    if not locations and name in {
        "tjg::color::basic_sgr_buffer", "tjg::color::sgr_buffer",
        "tjg::color::sgr_max_length", "tjg::color::sgr_reset_length",
    }:
        locations = symbols.get(name.replace("tjg::color::", "tjg::color::detail::"), [])
    if locations:
        matching_header = [loc for loc in locations if loc.get("file") == header_path]
        locations = matching_header or locations
        files = {loc.get("file") for loc in locations}
        if len(files) > 1:
            return header_path, None, "overloads across files"
        location = min(locations, key=lambda loc: int(loc.get("line", "1")))
        return location.get("file"), int(location.get("line", "1")), "declaration"
    # Implicit constructors, assignments, and comparisons have no source line.
    parent_name = name.rsplit("::", 1)[0]
    parent = classes.get(parent_name)
    if parent is not None:
        location = parent[1]
        return location.get("file"), int(location.get("line", "1")), "enclosing class"
    raise ValueError(f"No Doxygen location for {title}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--revision", required=True, help="Full source commit ID")
    parser.add_argument("--xml-dir", type=Path, default=Path("build/doxyxml"))
    parser.add_argument("--check", action="store_true", help="Report stale links without writing")
    parser.add_argument("--dry-run", action="store_true", help="Show source destinations without writing")
    args = parser.parse_args()
    if not re.fullmatch(r"[0-9a-f]{40}", args.revision):
        parser.error("--revision must be a full 40-character commit ID")
    root = Path(__file__).resolve().parents[1]
    xml_dir = root / args.xml_dir
    symbols, classes = load_symbols(xml_dir)
    updates = []
    linked = 0
    skipped = 0
    for page in sorted((root / "doc/ref").rglob("*.md")):
        raw = page.read_bytes()
        text = raw.decode("utf-8").replace("\r\n", "\n")
        first, rest = text.split("\n", 1)
        title = first.removeprefix("# ")
        # Make regeneration idempotent and preserve the exact visible title.
        old_link = re.fullmatch(r"\[(.*)\]\(https://github\.com/tjgolubi/color/blob/[^)]+\)", title)
        if old_link:
            title = old_link[1]
        target = source_target(title, text, symbols, classes)
        if target is None:
            skipped += 1
            continue
        source, line, reason = target
        source_file = root / source
        if not source_file.is_file():
            raise ValueError(f"Missing source file for {page}: {source}")
        if line is not None and not 1 <= line <= len(source_file.read_bytes().splitlines()):
            raise ValueError(f"Invalid source line for {page}: {line}")
        url = f"https://github.com/tjgolubi/color/blob/{args.revision}/{quote(source, safe='/')}"
        if line is not None:
            url += f"#L{line}"
        first = f"# [{title}]({url})"
        linked += 1
        if args.dry_run:
            print(f"{page.relative_to(root)} -> {source}:{line or '-'} ({reason})")
        updated = (first + "\n" + rest).replace("\n", "\r\n" if b"\r\n" in raw else "\n").encode("utf-8")
        if raw != updated:
            updates.append((page, raw, updated))
    print(f"{linked} source-linked titles; {skipped} topic titles unchanged; {len(updates)} updates.")
    if args.check:
        for page, _, _ in updates:
            print(f"Stale source title: {page.relative_to(root)}")
        return bool(updates)
    if not args.dry_run:
        for page, raw, updated in updates:
            if page.read_bytes() != raw:
                raise RuntimeError(f"Concurrent edit: {page}")
            page.write_bytes(updated)
    return False


if __name__ == "__main__":
    raise SystemExit(main())
