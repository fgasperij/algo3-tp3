#include "grafo.h"


Grafo::Grafo(int n) : matrizAdyacencia_(n, std::vector<float>(n)) {
}

Grafo::~Grafo() {
}

int Grafo::getCantidadVertices() const {
    return matrizAdyacencia_.size();
}

void Grafo::setPesoArista(int u, int v, float weight) {
    matrizAdyacencia_[u][v] = weight;
    matrizAdyacencia_[v][u] = weight;
}
float Grafo::getPesoArista(int u, int v) const {
    return matrizAdyacencia_[u][v];
}

float Grafo::getPesoAristasIncidentes(int u) const {
    float peso = 0;
    for (auto & pesoArista : matrizAdyacencia_[u]) {
        peso += pesoArista;
    }
    return peso;
}
