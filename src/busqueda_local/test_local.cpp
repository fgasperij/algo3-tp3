#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "grafo.h"
#include "heuristica.h"

#define MAX_N 30
#define MIN_N 3 // this depends on the test.in
#define INSTANCES_BY_SIZE 100

using namespace std;

double algoritmo_exacto(const vector<vector<double>> & adym, int k);
double busqueda_local_nodo_pasa(vector<vector<double> > &adym, vector<set<int> > partition, int max_it);
int busqueda_local_swap(vector<vector<double> > &adym, vector<set<int> > partition, int max_it);

int main()
{
  std::ofstream ofs_pesos("pesos_local.out", std::ofstream::out);
  std::ofstream ofs_ganador("ganador_local.out", std::ofstream::out);

  for (int cant_nodos = MIN_N; cant_nodos <= MAX_N; ++cant_nodos) {
    cout << "N: " << cant_nodos << endl;
    ofs_pesos << cant_nodos << ' ';
    ofs_ganador << cant_nodos << ' ';
    map<string, double> suma_de_pesos = {{"exacto", 0}, {"An", 0}, {"A10n", 0}, {"Bn", 0}, {"B10n", 0}};
    map<string, double> ganadas = {{"An", 0}, {"A10n", 0}};
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
      // resolvemos exacto
      double peso_exacto = algoritmo_exacto(adym, k);
      // resolvemos el goloso puro
      Heuristica h(g, k);
      vector<set<int>> greedy_partition =  h.resolverGolosoPuro();

      // ejecutamos A con n iteraciones
      double peso_a_n = busqueda_local_nodo_pasa(adym, greedy_partition, 10);
      // ejecutamos A con 10n iteraciones
      double peso_a_10n = busqueda_local_nodo_pasa(adym, greedy_partition, 100);
      // ejecutamos B con n iteraciones
      double peso_b_n = busqueda_local_swap(adym, greedy_partition, 10);
      // ejecutamos B con 10n iteraciones
      double peso_b_10n = busqueda_local_swap(adym, greedy_partition, 100);

      if (peso_a_n < peso_b_n) {
        ++ganadas["An"];
      }
      if (peso_a_10n < peso_b_n) {
        ++ganadas["A10n"];
      }

      suma_de_pesos["exacto"] += peso_exacto;
      suma_de_pesos["An"] += peso_a_n;
      suma_de_pesos["A10n"] += peso_a_10n;
      suma_de_pesos["Bn"] += peso_b_n;
      suma_de_pesos["B10n"] += peso_b_10n;
    }
    ofs_pesos << suma_de_pesos["exacto"]/INSTANCES_BY_SIZE << ' ' <<
      suma_de_pesos["An"]/INSTANCES_BY_SIZE << ' ' <<
      suma_de_pesos["A10n"]/INSTANCES_BY_SIZE << ' ' <<
      suma_de_pesos["Bn"]/INSTANCES_BY_SIZE << ' ' <<
      suma_de_pesos["B10n"]/INSTANCES_BY_SIZE << ' ' << endl;

    ofs_ganador << ganadas["An"] << ' ' << 100-ganadas["Bn"] << ' ' <<
      ganadas["A10n"] << ' ' << 100-ganadas["B10n"] << endl;

  }

  ofs_pesos.close();
  ofs_ganador.close();

  return 0;
}
