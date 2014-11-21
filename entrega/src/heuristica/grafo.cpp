#include "grafo.h"

Grafo::Grafo(int n) : matrizAdyacencia_(n, std::vector<double>(n)) {
}

Grafo::~Grafo() {
}

int Grafo::getCantidadVertices() const {
    return matrizAdyacencia_.size();
}

void Grafo::setPesoArista(int u, int v, double weight) {
    matrizAdyacencia_[u][v] = weight;
    matrizAdyacencia_[v][u] = weight;
}
double Grafo::getPesoArista(int u, int v) const {
    return matrizAdyacencia_[u][v];
}

double Grafo::getPesoAristasIncidentes(int u) const {
    double peso = 0;
    for (auto & pesoArista : matrizAdyacencia_[u]) {
        peso += pesoArista;
    }
    return peso;
}
