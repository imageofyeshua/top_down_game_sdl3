compile: build run

build:
	g++ -std=c++20 main.c player.c -o play.out `pkg-config --libs --cflags sdl3 sdl3-image`

run:
	./play.out
