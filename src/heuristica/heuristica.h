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
        void setK(int k);
        
        std::vector<std::set<int>> resolverGolosoPuro();
        std::vector<std::set<int>> resolver(int profundidadEleccionVertice = 1, int profundidadEleccionConjunto = 1);
    
    private:
        int pesoEnSubconjunto(int vertice, std::set<int> & conjuntoVertices);
        std::vector<int> ordenarPorPesoEnGrafo();
    
        Grafo grafo_{0};
        int k_{1};
};

#endif /* HEURISTICA_H */ 
