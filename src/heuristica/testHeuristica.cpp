#include "heuristica.h"
#include <iostream>

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int n, m, k, u, v, w;
    std::cin >> n >> m >> k;
    Grafo g(n);
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v >> w;
        g.setPesoArista(u - 1, v - 1, w);
    }
    Heuristica h(g,k);
    std::vector<std::set<int>> res = h.resolver(3,3);
    std::vector<int> conjuntoPorVertice(n);
    for ( int i = 0; i < k; i++) {
        for (auto & v : res[i]) {
            conjuntoPorVertice[v] = i;
        }
    }
    for (auto & conj : conjuntoPorVertice) {
        std::cout << conj + 1 << " ";
    }
    std::cout << std::endl;
    
    // Usando el algoritmo goloso original:
    //res = h.resolverGolosoPuro();
    //conjuntoPorVertice = std::vector<int>(n);
    //for ( int i = 0; i < k; i++) {
        //for (auto & v : res[i]) {
            //conjuntoPorVertice[v] = i;
        //}
    //}
    //for (auto & conj : conjuntoPorVertice) {
        //std::cout << conj + 1 << " ";
    //}
    //std::cout << std::endl;
    return 0;
}
