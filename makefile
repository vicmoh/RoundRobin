CC = gcc
CFLAGS = -Wall -g -linclude

program:
	$(CC) &(CFLAGS) src/*.c -o bin/run

run:
	./bin/run

valgrind:
	valgrind -v --leak-check=full ./bin/run
	