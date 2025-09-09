BIN = unsolvable_word_search
STD = c++17

CXX = g++
CXXFLAGS = -std=$(STD) \
	-W -Wall -Wextra -Wno-psabi -Werror \
	-pedantic -fexceptions
LDFLAGS = -lm -m64 -lzed

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS)
