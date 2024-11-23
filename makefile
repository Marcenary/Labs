CC=g++
CFLags=-c -Wall

all: test

test: main.o
	$(CC) main.o -o test

main.o: main.cpp

clean:
	rm -rf *.o test