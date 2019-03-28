CPP_FILES := $(wildcard *.cpp)
BIN_FILES := $(patsubst %.cpp,bin/%,$(CPP_FILES))

CPPFLAGS := -lSDL2 -lSDL2_gfx -Wall -Werror

build: $(BIN_FILES)

bin/%: %.cpp
	clang++ $^ $(CPPFLAGS) -o $@

clean:
	rm -f bin/ep*
