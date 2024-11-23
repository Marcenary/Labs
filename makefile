CC=g++
CFLags=-c -Wall
FILENAME=test

all: $(FILENAME)

build: main.o
	$(CC) main.o -o $(FILENAME).out

# add run with run *.out and clean *.o *.out

main.o: main.cpp

clean:
	rm -rf *.o $(FILENAME).out