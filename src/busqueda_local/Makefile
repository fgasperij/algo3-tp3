CXXFLAGS = -std=c++0x -Wall -O3
CC = clang++

all: test_local test_time
	
test_local: grafo.o heuristica.o test_local.o algoritmo_exacto.o busqueda_local_aislado.o
	$(CC) $(CXXFLAGS) grafo.o heuristica.o test_local.o algoritmo_exacto.o busqueda_local_aislado.o -o test_local

test_time: grafo.o heuristica.o busqueda_local_aislado.o test_local_time.o
	$(CC) $(CXXFLAGS) grafo.o heuristica.o test_local_time.o busqueda_local_aislado.o -o test_time

test_local_time.o: test_local_time.cpp
	$(CC) -c $(CXXFLAGS) test_local_time.cpp

algoritmo_exacto.o: algoritmo_exacto.cpp
	$(CC) -c $(CXXFLAGS) algoritmo_exacto.cpp

grafo.o: grafo.cpp
	$(CC) -c $(CXXFLAGS) grafo.cpp

heuristica.o: heuristica.cpp
	$(CC) -c $(CXXFLAGS) heuristica.cpp

test_local.o: test_local.cpp
	$(CC) -c $(CXXFLAGS) test_local.cpp

busqueda_local_aislado.o: busqueda_local_aislado.cpp
	$(CC) -c $(CXXFLAGS) busqueda_local_aislado.cpp

clean:
	rm -rf *.o
