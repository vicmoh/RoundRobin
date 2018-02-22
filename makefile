CC = gcc
CFLAGS = -Wall -g -Iinclude

program:
	$(CC) $(CFLAGS) src/*.c -o bin/run

run:
	./bin/run

valgrind:
	valgrind -v --leak-check=full ./bin/run
	