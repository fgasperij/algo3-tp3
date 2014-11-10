CXXFLAGS = -std=c++0x -Wall
CC = clang++

all: testHeuristica randomGen testComplejidad

testComplejidad: grafo.o heuristica.o testComplejidad.o
	$(CC) $(CXXFLAGS) testComplejidad.o heuristica.o grafo.o -o testComplejidad

randomGen: grafo.o heuristica.o randomGen.o
	$(CC) $(CXXFLAGS) randomGen.o heuristica.o grafo.o -o randomGen
	
testHeuristica: grafo.o heuristica.o testHeuristica.o
	$(CC) $(CXXFLAGS) testHeuristica.o heuristica.o grafo.o -o testHeuristica
	
grafo.o: grafo.cpp
	$(CC) -c $(CXXFLAGS) grafo.cpp
	
heuristica.o: heuristica.cpp
	$(CC) -c $(CXXFLAGS) heuristica.cpp
	
randomGen.o: randomGen.cpp
	$(CC) -c $(CXXFLAGS) randomGen.cpp

testHeuristica.o: testHeuristica.cpp
	$(CC) -c $(CXXFLAGS) testHeuristica.cpp

testComplejidad.o: testComplejidad.cpp
	$(CC) -c $(CXXFLAGS) testComplejidad.cpp

clean:
		rm -rf *o
