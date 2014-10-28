CXXFLAGS = -std=c++0x -Wall
CC = g++

all: testHeuristica
	
testHeuristica: heuristica.o testHeuristica.o
	$(CC) $(CXXFLAGS) testHeuristica.o heuristica.o -o testHeuristica
	
heuristica.o: heuristica.cpp
	$(CC) -c $(CXXFLAGS) heuristica.cpp

testHeuristica.o: testHeuristica.cpp
	$(CC) -c $(CXXFLAGS) testHeuristica.cpp

clean:
		rm -rf *o testHeuristica
