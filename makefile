CC=g++
CFLags=-c -Wall
FILENAME=test

all: $(FILENAME)

build: main.o
	$(CC) main.o -o $(FILENAME).out

# add run with run *.out and clean *.o *.out
# git branch --set-upstream-to=origin/master main
run:
	$(CC) main.o -o $(FILENAME).out
	./$(FILENAME).out
	rm -rf *.o $(FILENAME).out

main.o: main.cpp

clean:
	rm -rf *.o $(FILENAME).out