BIN = unsolvable_word_search
STD = c++17

CXX = g++
CXXFLAGS := -std=$(STD) \
	-W -Wall -Wextra -Wno-psabi -Werror \
	-pedantic -fexceptions
LDFLAGS = -lm -m64

ifneq ($(WINDOWS),)
CXX = x86_64-w64-mingw32-g++
BIN := $(BIN).exe
endif

ifeq ($(LIBZED),)
LDFLAGS += -lzed
else
LDFLAGS += -Wl,--gc-sections
STATICLIB = $(LIBZED)/libzed.a
CXXFLAGS += -I$(LIBZED)
endif

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: clean

$(BIN): $(OBJS) $(STATICLIB)
	$(CXX) -o $@ $^ $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS)
