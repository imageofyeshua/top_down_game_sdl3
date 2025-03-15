compile: build run

build:
	gcc \
	./src/*.c \
	./src/sdl/*.c \
	-o play.out \
	`pkg-config --libs --cflags sdl3 sdl3-image`

run:
	./play.out
