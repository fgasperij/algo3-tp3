CXXFLAGS = -std=c++0x -Wall
CC = g++

all: testHeuristica
	
testHeuristica: grafo.o heuristica.o testHeuristica.o
	$(CC) $(CXXFLAGS) testHeuristica.o heuristica.o grafo.o -o testHeuristica
	
grafo.o: grafo.cpp
	$(CC) -c $(CXXFLAGS) grafo.cpp
	
heuristica.o: heuristica.cpp
	$(CC) -c $(CXXFLAGS) heuristica.cpp

testHeuristica.o: testHeuristica.cpp
	$(CC) -c $(CXXFLAGS) testHeuristica.cpp

clean:
		rm -rf *o testHeuristica
