#ifndef GRASP_H
#define GRASP_H

#include "heuristica.h"

using namespace std;

class Grasp
{
    public:
        Grasp(Heuristica h);
        virtual ~Grasp();
        void ejecutar();
    private:
        bool pararMaximoIteraciones();
        bool pararIteracionesSinMejora();
        bool pararMaximoYSinMejoraJuntos();
        int pesoParticion(const vector<set<int>> & particion);
        void busquedaLocalUnNodo();
    
        Heuristica h_;
        vector<set<int>> particionActual_;
        vector<set<int>> mejorParticion_;
        unsigned int paradaMaximoIteraciones_{10000};
        unsigned int paradaIteracionesSinMejora_{1000};
        unsigned int iteracionActual_{0};
        unsigned int ultimaIteracionConMejora_{0};
        unsigned int pesoParticionActual_{0};
        unsigned int pesoMejorParticion_{0};
};

#endif /* GRASP_H */ 
