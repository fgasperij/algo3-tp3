CXXFLAGS = -std=c++0x -Wall -O3
CC = clang++

all: testGrasp tests
	
testGrasp: grafo.o heuristica.o grasp.o testGrasp.o
	$(CC) $(CXXFLAGS) grafo.o heuristica.o grasp.o testGrasp.o -o testGrasp

tests: grafo.o heuristica.o grasp.o algoritmo_exacto.o tests.o
	$(CC) $(CXXFLAGS) grafo.o heuristica.o grasp.o algoritmo_exacto.o tests.o -o tests
	
algoritmo_exacto.o:
	$(CC) -c $(CXXFLAGS) algoritmo_exacto.cpp

grafo.o: grafo.cpp
	$(CC) -c $(CXXFLAGS) grafo.cpp

heuristica.o: heuristica.cpp
	$(CC) -c $(CXXFLAGS) heuristica.cpp

grasp.o: grasp.cpp
	$(CC) -c $(CXXFLAGS) grasp.cpp

testGrasp.o: testGrasp.cpp
	$(CC) -c $(CXXFLAGS) testGrasp.cpp

tests.o: tests.cpp
	$(CC) -c $(CXXFLAGS) tests.cpp

clean:
	rm -rf *.o
