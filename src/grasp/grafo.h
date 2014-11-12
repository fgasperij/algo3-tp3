#ifndef GRAFO_H
#define GRAFO_H

#include <vector>

class Grafo
{
    public:
        Grafo(int n);
        virtual ~Grafo();
        
        int getCantidadVertices() const;
        
        // Los vertices se numeran de 0 a n-1 en los siguientes tres metodos
        void setPesoArista(int u, int v, int weight);
        int getPesoArista(int u, int v) const;
        int getPesoAristasIncidentes(int u) const;
    private:
        std::vector<std::vector<int>> matrizAdyacencia_;
};

#endif /* GRAFO_H */ 
