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
        double pesoEnSubconjunto(int vertice, std::set<int> & conjuntoVertices);
        void setProfundidadEleccionVertice(int profundidadEleccionVertice);
        void setProfundidadEleccionConjunto(int profundidadEleccionConjunto);
        
        std::vector<std::set<int>> resolverGolosoPuro();
        std::vector<std::set<int>> resolver();
    
    private:
        std::vector<int> ordenarPorPesoEnGrafo();
    
        Grafo grafo_{0};
        int k_{1};
        int profundidadEleccionVertice_{4};
        int profundidadEleccionConjunto_{4};
};

#endif /* HEURISTICA_H */ 
