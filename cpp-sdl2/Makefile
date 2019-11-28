CPP_FILES := $(wildcard *.cpp)
BIN_FILES := $(patsubst %.cpp,bin/%,$(CPP_FILES))

CPPFLAGS := -lSDL2 -lSDL2_gfx -Wall -Werror -std=c++17

build: $(BIN_FILES)

bin/%: %.cpp
	clang++ $^ $(CPPFLAGS) -o $@

tidy:
	clang-tidy ep02.cpp -- $(CPPFLAGS)

clean:
	rm -f bin/ep*
