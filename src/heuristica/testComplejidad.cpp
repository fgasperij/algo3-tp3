#include "heuristica.h"
#include <chrono>
#include <iostream>
#include <climits>

const int CANT_INSTANCIAS = 100;
const int MIN_VERTICES = 2;
const int MAX_VERTICES = 100;
const int CANT_REPETICIONES_CALCULO_INSTANCIA = 5;
const int MAX_K = 100;
const int K_STEP = 10;

int main(int argc, const char* argv[]) {
    for (int cantVertices = MIN_VERTICES; cantVertices <= MAX_VERTICES; cantVertices++) {
        std::cout << cantVertices << " ";
        std::vector<int> sumaTiemposPorK(MAX_K / K_STEP);
        for (int instancia = 1; instancia <= CANT_INSTANCIAS; instancia++) {
            int n, m, u, v;
            float w;
            std::cin >> n >> m;
            Grafo g(n);
            for (int i = 0; i < m; i++) {
                std::cin >> u >> v >> w;
                g.setPesoArista(u - 1, v - 1, w);
            }
            for (int k = K_STEP; k <= MAX_K; k += K_STEP) {
                Heuristica h(g,k);
                std::chrono::microseconds minTiempo(INT_MAX);
                for (int rep = 1; rep <= CANT_REPETICIONES_CALCULO_INSTANCIA; rep++) {
                    auto start_time = std::chrono::high_resolution_clock::now();
                    h.resolverGolosoPuro();
                    auto end_time = std::chrono::high_resolution_clock::now();
                    std::chrono::microseconds tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
                    if (tiempoRep < minTiempo)
                        minTiempo = tiempoRep;
                }
                sumaTiemposPorK[k / K_STEP - 1] += minTiempo.count();
            }
        }
        for (auto & tiempos : sumaTiemposPorK)
            tiempos /= CANT_INSTANCIAS;
        for (auto promedio : sumaTiemposPorK)
            std::cout << promedio << " ";
        std::cout << std::endl;
    }
    
    return 0;
}
