CC=gcc

FAST=-Ofast

dir = .


all: main

main: main.c
	$(CC) $(FAST) -o $(dir)/main main.c

clean:
	rm $(dir)/main