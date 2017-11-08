CC=gcc

CFLAG=-O3
PRINT=-D_PRINT_
TEST=-D_TEST_

dir = .

all: main 

main: main.c
	$(CC) $(CFLAG) $(PRINT) -o $(dir)/main main.c

test: main.c
	$(CC) $(CFLAG) $(TEST) -o $(dir)/main main.c


.PHONY: clean
clean:
	rm -f $(dir)/main || del main.exe
