CC=gcc

CFLAG=-O3

dir = .

$(rm -f)
res=$?

all: main

main: main.c
	$(CC) $(CFLAG) -o $(dir)/main main.c

.PHONY: clean
clean:
ifeq ($res, 0)
	rm -f $(dir)/main
else
	del	main.exe
endif
