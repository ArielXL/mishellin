all: build run

build:
	gcc -o mishellin.out src/*.c src/commands/*.c src/history/*.c src/utilities/*.c
run:
	./mishellin.out