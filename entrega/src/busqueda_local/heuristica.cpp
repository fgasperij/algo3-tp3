#include "heuristica.h"
#include <algorithm>
#include <climits>
#include <cstdlib>

Heuristica::Heuristica()
{
}

Heuristica::Heuristica(Grafo & grafo, int k) : grafo_(grafo), k_(k)
{
}

Heuristica::~Heuristica()
{
}

void Heuristica::setGrafo(Grafo & grafo) {
    grafo_ = grafo;
}

void Heuristica::setK(int k) {
    k_ = k;
}

void Heuristica::setProfundidadEleccionVertice(int profundidadEleccionVertice) {
    profundidadEleccionVertice_ = profundidadEleccionVertice;
}
void Heuristica::setProfundidadEleccionConjunto(int profundidadEleccionConjunto) {
    profundidadEleccionConjunto_ = profundidadEleccionConjunto;
}

// Ordena los vertices en el grafo de mayor a menor segun su peso, donde peso de un vertice es la suma de las aristas incidentes
std::vector<int> Heuristica::ordenarPorPesoEnGrafo() {
    std::vector<std::pair<int,double>> infoVertices; // Esto guarda las tuplas <vertice, peso(vertice)>
    int n = grafo_.getCantidadVertices();
    for (int i = 0; i < n; i++) {
        infoVertices.push_back(std::make_pair(i, grafo_.getPesoAristasIncidentes(i)));
    }
    std::sort(infoVertices.begin(), infoVertices.end(), [](const std::pair<int,double> & a, const std::pair<int,double> & b) { return a.second > b.second; });
    std::vector<int> res;
    for (auto & v : infoVertices) {
        res.push_back(v.first);
    }
    return res;
}

double Heuristica::pesoEnSubconjunto(int vertice, std::set<int> & conjuntoVertices) {
    double peso = 0;
    for (auto & otroVertice : conjuntoVertices) {
        peso += grafo_.getPesoArista(vertice, otroVertice);
    }
    return peso;
}

std::vector<std::set<int>> Heuristica::resolverGolosoPuro() {
    std::vector<std::set<int>> res(k_);
    int n = grafo_.getCantidadVertices();
    if (n <= k_) {
        for (int i = 0; i < n; i++) {
            res[i].insert(i);
        }
    } else {
        std::vector<int> verticesOrdenadosPorPeso = ordenarPorPesoEnGrafo();
        for (auto & v : verticesOrdenadosPorPeso) {
            double mejorPeso = pesoEnSubconjunto(v, res[0]);
            int mejorSubconjunto = 0;
            for (int i = 1; i < k_; i++) {
                int pesoEnSubconj = pesoEnSubconjunto(v, res[i]);
                if ( pesoEnSubconj < mejorPeso ) {
                    mejorPeso = pesoEnSubconj;
                    mejorSubconjunto = i;
                }
            }
            res[mejorSubconjunto].insert(v);
        }
    }
    return res;
}

std::vector<std::set<int>> Heuristica::resolver() {
    std::vector<std::set<int>> res(k_);
    std::vector<int> verticesOrdenadosPorPeso = ordenarPorPesoEnGrafo();
    int cantidadConjuntosCandidatos = std::min(k_, profundidadEleccionConjunto_);
    while (!verticesOrdenadosPorPeso.empty()) {
        int cantidadVerticesCandidatos = std::min((int)verticesOrdenadosPorPeso.size(), profundidadEleccionVertice_);
        int indicePorRemover = rand() % cantidadVerticesCandidatos;
        int verticeNuevo = verticesOrdenadosPorPeso[indicePorRemover];
        verticesOrdenadosPorPeso.erase(verticesOrdenadosPorPeso.begin() + indicePorRemover);
        std::vector<std::pair<int,double>> infoConjuntos; // Esto guarda las tuplas <conjunto i, peso del vertice en conjunto i>
        for (int i = 0; i < k_; i++) {
            infoConjuntos.push_back(std::make_pair(i, pesoEnSubconjunto(verticeNuevo, res[i])));
        }
        std::sort(infoConjuntos.begin(), infoConjuntos.end(), [] (const std::pair<int,double> & a, const std::pair<int,double> & b) { return a.second < b.second; });
        res[infoConjuntos[rand() % cantidadConjuntosCandidatos].first].insert(verticeNuevo);
    }
    return res;
}

