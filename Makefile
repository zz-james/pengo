CXX      = g++
CXXFLAGS = -std=c++17 -I Pengo/Pengo/Source -I Pengo/Pengo/External_Libraries $(shell pkg-config --cflags sdl2)
LIBS     = -lSDL2 -lSDL2_image -lSDL2_mixer
SRC      = $(wildcard Pengo/Pengo/Source/*.cpp)
OUT      = Pengo/Pengo/Game/pengo

.PHONY: all clean

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

clean:
	rm -f $(OUT)
