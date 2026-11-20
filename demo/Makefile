CXX = g++
TJG_ROOT = ..
TJG_BUILD ?= $(TJG_ROOT)/build
TJG_LIB ?= $(TJG_BUILD)/libcolor.a
FMT_ROOT ?= $(HOME)/App/fmt
FMT_LIB ?= $(FMT_ROOT)/build/libfmtd.a
CXXFLAGS += -std=gnu++23 -Wall -Wextra -Werror

TJG_DEMOS := StyledDemo StyledTextDemo
TJG_DEMOS += TableDemo TableDemoCpp TableDemoOstream
FMT_DEMOS := Result42Compare TableDemoFmt
DEMOS := $(TJG_DEMOS) $(FMT_DEMOS)

find_headers = $(wildcard $(1)*.h $(1)*.hpp) \
               $(foreach dir,$(wildcard $(1)*/),$(call find_headers,$(dir)))
TJG_HEADERS := $(call find_headers,$(TJG_ROOT)/include/tjg/)
TJG_SOURCES := $(wildcard $(TJG_ROOT)/src/*.cpp $(TJG_ROOT)/src/*.hpp)

.PHONY: all run clean
all: $(DEMOS)

$(DEMOS): %: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

$(DEMOS): CPPFLAGS += -I$(TJG_ROOT)/include
$(DEMOS): $(TJG_HEADERS)
$(DEMOS): LDLIBS += "$(TJG_LIB)"
$(DEMOS): $(TJG_LIB)

$(TJG_LIB): $(TJG_HEADERS) $(TJG_SOURCES) $(TJG_ROOT)/CMakeLists.txt
	cmake -S "$(TJG_ROOT)" -B "$(TJG_BUILD)"
	cmake --build "$(TJG_BUILD)" --target tjg --parallel 4

$(FMT_DEMOS): CPPFLAGS += -I"$(FMT_ROOT)/include"
$(FMT_DEMOS): LDLIBS += "$(FMT_LIB)"
$(FMT_DEMOS): $(FMT_LIB)

run: all
	./Result42Compare
	./StyledDemo
	./StyledTextDemo
	./TableDemo
	./TableDemoCpp
	./TableDemoFmt
	./TableDemoOstream

clean:
	$(RM) $(DEMOS)
