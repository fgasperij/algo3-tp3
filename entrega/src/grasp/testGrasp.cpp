#include "grasp.h"
#include <iostream>

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int n, m, k, u, v;
    double w;
    std::cin >> n >> m >> k;
    Grafo g(n);
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v >> w;
        g.setPesoArista(u - 1, v - 1, w);
    }
    Heuristica h(g,k);
    Grasp grasp(h);
    grasp.setParadaMaximoIteraciones(15000);
    grasp.setParadaIteracionesSinMejora(2000);
    grasp.setProfundidadEleccionConjunto(4);
    grasp.setProfundidadEleccionVertice(4);
    grasp.ejecutar(Grasp::pararPorMaximoYPorSinMejora);
    Grasp::imprimirParticion(grasp.getMejorParticion(), n);
    return 0;
}
