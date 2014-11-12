#ifndef HEURISTICA_H
#define HEURISTICA_H

#include <vector>
#include <set>
#include "grafo.h"

class Heuristica
{
    public:
        Heuristica();
        Heuristica(Grafo & grafo, int k);
        virtual ~Heuristica();
        void setGrafo(Grafo & grafo);
        const Grafo & getGrafo() { return grafo_; }
        void setK(int k);
        int getK() { return k_; }
        int pesoEnSubconjunto(int vertice, std::set<int> & conjuntoVertices);
        
        std::vector<std::set<int>> resolverGolosoPuro();
        std::vector<std::set<int>> resolver(int profundidadEleccionVertice = 5, int profundidadEleccionConjunto = 5);
    
    private:
        std::vector<int> ordenarPorPesoEnGrafo();
    
        Grafo grafo_{0};
        int k_{1};
};

#endif /* HEURISTICA_H */ 
