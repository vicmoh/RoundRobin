CC = gcc
CFLAGS = -Wall -g -Iinclude -std=c11

program:
	$(CC) $(CFLAGS) src/*.c -o bin/run

run:
	./bin/run

run1:
	./bin/run -r 10 < ./assets/testcase1.txt

run2:
	./bin/run -d -r 10 < ./assets/testcase1.txt

run3:
	./bin/run -v 10 < ./assets/testcase1.txt

valgrind:
	valgrind -v --leak-check=full ./bin/run
	