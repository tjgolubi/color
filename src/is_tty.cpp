/// @copyright 2026 Terry Golubiewski, all rights reserved.
#include <tjg/color/bits/text_style-format.hpp>

#include <system_error>

#if defined(_WIN32) && !defined(__CYGWIN__) && !defined(__MSYS__)
#include <io.h>
#else
#include <unistd.h>
#endif

namespace tjg::color::detail {

[[nodiscard]] auto is_tty(FILE* fp) noexcept -> bool {
  if (!fp)
    return false;

#if defined(_WIN32) && !defined(__CYGWIN__) && !defined(__MSYS__)
  // The Windows CRT also recognizes character devices other than terminals.
  const int fd = ::_fileno(fp);
  return fd >= 0 && ::_isatty(fd) != 0;
#else
  const int fd = ::fileno(fp);
  return fd >= 0 && ::isatty(fd) == 1;
#endif
} // is_tty

} // tjg::color::detail
