// Este programa va a mostrar por pantalla CANT_INSTANCIAS grafos aleatorios de N vértices, para cada N = 1, ..., MAX_VERTICES.
// Hay que usar ./randomGen > textFile para guardar a disco.
// g++ -O3 randomGen.cpp -o randomGen

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <set>

using namespace std;

typedef int Vertice;

const int CANT_INSTANCIAS = 100;
const int MAX_VERTICES = 100;
const int MAX_COSTO_ARISTA = 100;

Vertice seleccionarVerticeRandom(set<Vertice> & conjunto) {
    int i = rand() % conjunto.size();
    auto it = conjunto.begin();
    for(int j = 0; j < i; j++) it++;
    return *it;
}

int main(int argc, const char* argv[]) {
    srand(time(NULL) + getpid()); // Seedeo
    for (int n = 1; n <= MAX_VERTICES; n++) {
        for (int i = 1; i <= CANT_INSTANCIAS; i++) {
            int m = rand() % (1 + n * (n - 1) / 2); // m es un valor aleatorio entre 0 y n(n-1)/2
            cout << n << " " << m << endl;
            set<Vertice> vertices; // Acá voy a tener el conjunto de vértices que todavía al menos una arista disponible.
            for (int i = 0; i < n; i++) {
                vertices.insert(i); // Los vertices van a ser enteros entre 0 y n-1, tengo que sumarles uno al imprimir
            }
            vector< set<Vertice> > vecinosPosibles(n);
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
                    cout << v + 1 << " " << w + 1 << " " << (rand() % MAX_COSTO_ARISTA) + 1 << endl;
                }
            }
        }
    }
}

