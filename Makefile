CC=gcc
FILES=./src/main.c
FLAGS=-ggdb -Wall -Wextra -std=c99 -pedantic
LIBS=-lglfw -lGLEW -lGL

all:
	$(CC) $(FLAGS) $(FILES) $(LIBS) -o a.out

clean:
	rm *.out
	rm *.o
