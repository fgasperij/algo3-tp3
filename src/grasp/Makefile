CXXFLAGS = -std=c++0x -Wall
CC = clang++

all: testGrasp randomGen

#testComplejidad: grafo.o heuristica.o testComplejidad.o
#	$(CC) $(CXXFLAGS) testComplejidad.o heuristica.o grafo.o -o testComplejidad

randomGen: grafo.o heuristica.o randomGen.o
	$(CC) $(CXXFLAGS) randomGen.o heuristica.o grafo.o -o randomGen
	
testGrasp: grafo.o heuristica.o grasp.o testGrasp.o
	$(CC) $(CXXFLAGS) grafo.o heuristica.o grasp.o testGrasp.o -o testGrasp

grafo.o: grafo.cpp
	$(CC) -c $(CXXFLAGS) grafo.cpp

heuristica.o: heuristica.cpp
	$(CC) -c $(CXXFLAGS) heuristica.cpp

grasp.o: grasp.cpp
	$(CC) -c $(CXXFLAGS) grasp.cpp
	
randomGen.o: randomGen.cpp
	$(CC) -c $(CXXFLAGS) randomGen.cpp

testGrasp.o: testGrasp.cpp
	$(CC) -c $(CXXFLAGS) testGrasp.cpp

#testComplejidad.o: testComplejidad.cpp
#	$(CC) -c $(CXXFLAGS) testComplejidad.cpp

clean:
		rm -rf *o
