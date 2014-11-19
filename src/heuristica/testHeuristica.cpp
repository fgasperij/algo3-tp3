#include "heuristica.h"
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
    std::vector<std::set<int>> res = h.resolver();
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
    return 0;
}
