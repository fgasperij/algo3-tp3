// Este programa va a mostrar por pantalla CANT_INSTANCIAS instancias de k-PMP. Es decir, grafos aleatorios de N vértices, para cada N = MIN_VERTICES, ..., MAX_VERTICES con 0.7*N(N-1)/2 <= m <= N(N-1)/2 y 2 <= k <= max(2, N/3).
// CANT_INSTANCIAS, MIN_VERTICES, MAX_VERTICES, y MAX_COSTO_ARISTA se configuran en configuracionGeneracionInstancias.txt (en ese archivo se explica cómo).
// Hay que usar ./randomGen > textFile para guardar a disco.
// g++ -Wall -O3 randomGen.cpp -o randomGen

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <set>
#include <climits>
#include <fstream>
#include <algorithm>

using namespace std;

typedef int Vertice;

int CANT_INSTANCIAS;
int MIN_VERTICES;
int MAX_VERTICES;
double MAX_COSTO_ARISTA;

Vertice seleccionarVerticeRandom(const set<Vertice> & conjunto) {
    int i = rand() % conjunto.size();
    auto it = conjunto.begin();
    for(int j = 0; j < i; j++) it++;
    return *it;
}

int main(int argc, const char* argv[]) {
    ifstream archivoConfiguracion("configuracionGeneracionInstancias.txt");
    archivoConfiguracion >> CANT_INSTANCIAS >> MIN_VERTICES >> MAX_VERTICES >> MAX_COSTO_ARISTA;
    archivoConfiguracion.close();
    srand(time(NULL) + getpid()); // Seedeo
    cout.precision(4);
    for (int n = MIN_VERTICES; n <= MAX_VERTICES; n++) {
        const int m_maximo = n * (n - 1) / 2; // Cantidad de aristas del grafo completo de n nodos
        const int m_minimo = 0.7 * m_maximo; // Minima cantidad de aristas de los grafos generados
        const int k_minimo = 2; // Minimo k de las instancias generadas
        const int k_maximo = max(k_minimo, n / 3); // Maximo k de las instancias generadas
        for (int i = 1; i <= CANT_INSTANCIAS; i++) {
            int m = m_minimo + rand() % (m_maximo - m_minimo + 1); // m es un valor aleatorio entre m_minimo y m_maximo
            int k = k_minimo + rand() % (k_maximo - k_minimo + 1); // k es un valor aleatorio entre k_minimo y k_maximo
            cout << n << " " << m << " " << k << endl;
            set<Vertice> vertices; // Vértices que todavía tienen al menos una arista disponible
            for (int i = 0; i < n; i++) {
                vertices.insert(i); // Los vertices van a ser enteros entre 0 y n-1, tengo que sumarles uno al imprimir
            }
            vector<set<Vertice>> vecinosPosibles(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        vecinosPosibles[i].insert(j);
                    }
                }
            }
            while (m > 0) {
                Vertice v = seleccionarVerticeRandom(vertices);
                if (vecinosPosibles[v].size() == 0) {
                    vertices.erase(v);
                } else {
                    m--;
                    Vertice w = seleccionarVerticeRandom(vecinosPosibles[v]);
                    vecinosPosibles[v].erase(w);
                    vecinosPosibles[w].erase(v);
                    double weight = MAX_COSTO_ARISTA * (static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
                    if (weight == 0.f) { // 0.f es equivalente a no tener arista, hay que arreglarlo
                        weight += 0.0001; // Esto sólo tiene sentido para cout.precision(r) con r >= 4
                    }
                    cout << v + 1 << " " << w + 1 << " " << fixed << weight << endl;
                }
            }
        }
    }
    return 0;
}

