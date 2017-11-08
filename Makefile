CC=gcc

CFLAG=-O3

dir = .


all: main

main: main.c
	$(CC) $(CFLAG) -o $(dir)/main main.c

clean:
	rm $(dir)/main