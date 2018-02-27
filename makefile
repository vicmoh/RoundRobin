CC = gcc
CFLAGS = -Wall -g -Iinclude -std=c11

program:
	$(CC) $(CFLAGS) src/*.c -o bin/run

run:
	./bin/run

FCFS:
	./bin/run -r 10 < ./assets/testcase1.txt

RoundRobin:
	./bin/run -d -r 10 < ./assets/testcase1.txt

Verbose:
	./bin/run -v 10 < ./assets/testcase1.txt

valgrind:
	valgrind -v --leak-check=full ./bin/run
	
clean:
	rm bin/*