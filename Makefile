CXX = g++
FILES = 3sdl.cpp
LIBRARIES = -lSDL -lSDL_image
EXE = sdl

all: $(FILES)
	$(CXX) $(FILES) -g -Wall -w -pedantic -time $(LIBRARIES) -o $(EXE)

clean:
	rm -f *.o $(EXE)
