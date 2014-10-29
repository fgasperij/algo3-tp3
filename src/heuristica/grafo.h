#ifndef GRAFO_H
#define GRAFO_H

#include <vector>

class Grafo
{
    public:
        Grafo(int n);
        virtual ~Grafo();
        
        int getCantidadVertices();
        void setPesoArista(int u, int v, int weight);
        int getPesoArista(int u, int v);
        int getPesoAristasIncidentes(int u);
    private:
        std::vector<std::vector<int>> matrizAdyacencia_;
};

#endif /* GRAFO_H */ 
