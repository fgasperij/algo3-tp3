CXXFLAGS = -std=c++0x -Wall -O3
CC = g++

all: randomGen

randomGen: randomGen.o
	$(CC) $(CXXFLAGS) randomGen.o -o randomGen
	
randomGen.o: randomGen.cpp
	$(CC) -c $(CXXFLAGS) randomGen.cpp

clean:
		rm -rf *.o
