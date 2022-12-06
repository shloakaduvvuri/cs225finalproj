

CC = g++
CFLAGS = -Wall -g

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

test: tests.o
	$(CC) $(CFLAGS) -o test tests.o

tests.o: tests/tests.cpp
	$(CC) $(CFLAGS) -c tests/tests.cpp