#include "heuristica.h"
#include <algorithm>
#include <climits>

Heuristica::Heuristica(Grafo & grafo, int k) : grafo_(grafo), k_(k)
{
}

Heuristica::~Heuristica()
{
    
}

// Ordena los vertices en el grafo de mayor a menor segun su peso, donde peso de un vertice es la suma de las aristas incidentes
std::vector<int> Heuristica::ordenarPorPesoEnGrafo() {
    std::vector<std::pair<int,int>> infoVertices;
    int n = grafo_.getCantidadVertices();
    for (int i = 0; i < n; i++) {
        infoVertices.push_back(std::make_pair(i, grafo_.getPesoAristasIncidentes(i)));
    }
    std::sort(infoVertices.begin(), infoVertices.end(), [](const std::pair<int,int> & a, const std::pair<int,int> & b) { return a.second > b.second; });
    std::vector<int> res;
    for (auto & v : infoVertices) {
        res.push_back(v.first);
    }
    return res;
}

int Heuristica::pesoEnSubconjunto(int vertice, std::set<int> & conjuntoVertices) {
    int peso = 0;
    for (auto & otroVertice : conjuntoVertices) {
        peso += grafo_.getPesoArista(vertice, otroVertice);
    }
    return peso;
}

std::vector<std::set<int>> Heuristica::resolver() {
    std::vector<std::set<int>> res(k_);
    std::vector<int> verticesOrdenadosPorPeso = ordenarPorPesoEnGrafo();
    for (auto & v : verticesOrdenadosPorPeso) {
        int mejorPeso = INT_MAX;
        int mejorSubconjunto = 0;
        for (int i = 0; i < k_; i++) {
            int pesoEnSubconj = pesoEnSubconjunto(v, res[i]);
            if ( pesoEnSubconj < mejorPeso ) {
                mejorPeso = pesoEnSubconj;
                mejorSubconjunto = i;
            }
        }
        res[mejorSubconjunto].insert(v);
    }
    return res;
}

