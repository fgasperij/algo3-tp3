#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <climits>
#include "grafo.h"
#include "heuristica.h"

#define MAX_N 75
#define MIN_N 3 // this depends on the test.in
#define INSTANCES_BY_SIZE 100

using namespace std;

double busqueda_local_nodo_pasa(vector<vector<double> > &adym, vector<set<int> > partition, int max_it);
int busqueda_local_swap(vector<vector<double> > &adym, vector<set<int> > partition, int max_it);

int main()
{
  std::ofstream ofs("time_local.out", std::ofstream::out);

  for (int cant_nodos = MIN_N; cant_nodos <= MAX_N; ++cant_nodos) {
    cout << "N: " << cant_nodos << endl;
    ofs << cant_nodos << ' ';
    map<string, int> tiempos = {{"A", 0}, {"B", 0}};
    for (int instance = 0; instance < INSTANCES_BY_SIZE; ++instance) {
      cout << "instancia: " << instance << endl;
      // parsear entrada a Grafo
      // parsear entrada a ADYM
      int n, m, k, u, v;
      double w;
      std::cin >> n >> m >> k;
      Grafo g(n);
      vector<vector<double>> adym(n, vector<double> (n, 0));
      for (int i = 0; i < m; i++) {
          std::cin >> u >> v >> w;
          g.setPesoArista(u - 1, v - 1, w);
          adym[u - 1][v - 1] = w;
          adym[v - 1][u - 1] = w;
      }
      // resolvemos el goloso puro
      Heuristica h(g, k);
      vector<set<int>> greedy_partition =  h.resolverGolosoPuro();

      // ejecutamos A con 10n iteraciones
      std::chrono::microseconds minTiempoA(INT_MAX);
      for (int i = 0; i < 10; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();
        busqueda_local_nodo_pasa(adym, greedy_partition, 100);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        if (tiempoRep < minTiempoA) {
            minTiempoA = tiempoRep;
        }
      }
      tiempos["A"] += minTiempoA.count();

      // ejecutamos B con 10n iteraciones
      std::chrono::microseconds minTiempoB(INT_MAX);
      for (int i = 0; i < 10; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();
        busqueda_local_swap(adym, greedy_partition, 100);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        if (tiempoRep < minTiempoB) {
            minTiempoB = tiempoRep;
        }
      }
      tiempos["B"] += minTiempoB.count();

    }
    ofs << tiempos["A"]/INSTANCES_BY_SIZE << ' ' <<
      tiempos["B"]/INSTANCES_BY_SIZE <<  endl;
  }

  ofs.close();

  return 0;
}
