#include "grafo.h"


Grafo::Grafo(int n) : matrizAdyacencia_(n, std::vector<int>(n)) {
}

Grafo::~Grafo() {
}

int Grafo::getCantidadVertices() {
    return matrizAdyacencia_.size();
}

void Grafo::setPesoArista(int u, int v, int weight) {
    matrizAdyacencia_[u][v] = weight;
    matrizAdyacencia_[v][u] = weight;
}
int Grafo::getPesoArista(int u, int v) {
    return matrizAdyacencia_[u][v];
}

int Grafo::getPesoAristasIncidentes(int u) {
    int peso = 0;
    for (auto & pesoArista : matrizAdyacencia_[u]) {
        peso += pesoArista;
    }
    return peso;
}
