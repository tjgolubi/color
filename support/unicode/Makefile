PROJDIR := $(abspath ../..)

CXXFLAGS += -std=c++23 -Wall -Wextra -Wpedantic -Werror
BUILD_DIR ?= ./build
PYTHON ?= python3
CURL ?= curl

UNICODE_VERSION := 18.0.0
UCD_URL := https://www.unicode.org/Public/$(UNICODE_VERSION)/ucd
UCD_FILES := UnicodeData.txt EastAsianWidth.txt PropList.txt LineBreak.txt

ifneq ($(filter MSYS%,$(shell uname -s)),)
# MSYS libstdc++ <print> needs stdio declarations hidden in strict C++ mode.
CPPFLAGS += -D_DEFAULT_SOURCE
endif

ifeq ($(OS),Windows_NT)
EXEEXT ?= .exe
endif

PRG1 := GenWideRanges
PRG2 := GenUnicodeTables

BIN1 := $(addprefix $(BUILD_DIR)/,$(addsuffix $(EXEEXT),$(PRG1)))
BIN2 := $(addprefix $(BUILD_DIR)/,$(addsuffix $(EXEEXT),$(PRG2)))

BINARIES := $(BIN1) $(BIN2)

INCLUDE := $(PROJDIR)/include/tjg/color/bits

.PHONY: all clean download
all: $(PROJDIR)/src/UnicodeData.hpp $(INCLUDE)/EastAsianWidth.hpp \
     $(PROJDIR)/src/WrapData.hpp

download:
	@set -e; for input in $(UCD_FILES); do \
	  if [ -e "$$input" ]; then continue; fi; \
	  ( \
	    temp=$$(mktemp "./.$$input.XXXXXX"); \
	    trap 'rm -f -- "$$temp"' EXIT; \
	    $(CURL) --fail --location --output "$$temp" "$(UCD_URL)/$$input"; \
	    mv -n -- "$$temp" "$$input"; \
	  ); \
	done

$(PROJDIR)/src/WrapData.hpp: gen-wrap-tables.py UnicodeData.txt PropList.txt LineBreak.txt
	$(PYTHON) gen-wrap-tables.py

$(BUILD_DIR)/%$(EXEEXT): %.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) "$<" $(LDLIBS) -o "$@"

$(INCLUDE)/EastAsianWidth.hpp: $(BIN1) EastAsianWidth.txt
	$(BIN1) EastAsianWidth.txt > $@

$(PROJDIR)/src/UnicodeData.hpp: $(BIN2) UnicodeData.txt
	$(BIN2) UnicodeData.txt > $@

$(BUILD_DIR):
	mkdir -p "$@"

clean:
	$(RM) -- $(BINARIES)
