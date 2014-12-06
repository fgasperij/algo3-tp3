#include "grasp.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <cfloat>
#include <chrono>
#include <climits>
#include <set>
#include <vector>

using namespace std;

double algoritmo_exacto(const vector<vector<double>> & adym, int k);

double pesoParticion(const Grafo & grafo, vector<set<int>> & particion) {
    double res = 0;
    for (auto & conjunto : particion) {
        for (auto i = conjunto.begin(); i != conjunto.end(); i++) {
            int v = *i;
            auto j = i;
            j++;
            while (j != conjunto.end()) {
                res += grafo.getPesoArista(v, *j);
                j++;
            }
        }
    }
    return res;
}

int CANT_INSTANCIAS;
int MIN_VERTICES;
int MAX_VERTICES;
const int EXACTO_MAX_VERTICES = 23;
const int CANT_REPETICIONES_CALCULO_INSTANCIA = 1;

void testCalidadVsExacto(int max_vertices) { // Requiere max_vertices <= MAX_VERTICES
    int profVert = 4;
    int profConj = 4;
    vector<int> maximoIteraciones = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    vector<double> promedios(maximoIteraciones.size());
    
    for (int cantVertices = MIN_VERTICES; cantVertices <= max_vertices; cantVertices++) {
        cout << cantVertices << " ";
        for (int instancia = 1; instancia <= CANT_INSTANCIAS; instancia++) {
            int n, m, k, u, v;
            double w;
            std::cin >> n >> m >> k;
            Grafo g(n);
            vector<vector<double>> adym(n, vector<double> (n, 0));
            for (int i = 0; i < m; i++) {
                std::cin >> u >> v >> w;
                g.setPesoArista(u - 1, v - 1, w);
                adym[u - 1][v - 1] = w;
                adym[v - 1][u - 1] = w;
            }
            double pesoExacto = algoritmo_exacto(adym, k);
            if (pesoExacto < 0.1f) {
                pesoExacto = 0.1f; // Para evitar divisiones por cero al hacer pesoGrasp / pesoExacto
            }
            Heuristica h(g,k);
            for (int i = 0; i < maximoIteraciones.size(); i++) {
                Grasp grasp(h);
                grasp.setParadaIteracionesSinMejora(maximoIteraciones[i]);
                grasp.setProfundidadEleccionVertice(profVert);
                grasp.setProfundidadEleccionConjunto(profConj);
                double pesoGrasp = grasp.ejecutar(Grasp::pararPorIteracionesSinMejora);
                if (pesoGrasp < 0.1f) {
                    pesoGrasp = 0.1f; // Si fueran ambos pesos 0.0, con esto me aseguro que pesoGrasp / pesoExacto = 1.0
                }
                double errorRelativo = 100.0 * (pesoGrasp - pesoExacto) / pesoExacto;
                if (abs(errorRelativo) < 0.1) {
                    errorRelativo = abs(errorRelativo); // Con esto nos evitamos sumar errores negativos producto del error de cálculo inherente a la aritmética finita.
                }
                promedios[i] += errorRelativo; // Qué tanto más pesada es la solución de la GRASP en relación a la solución óptima, en porcentaje (si pesoGrasp fuera el doble que pesoExacto, daría 100%).
            }
        }
        for (auto & p : promedios) {
            p /= CANT_INSTANCIAS;
            cout << fixed << p << " ";
        }
        cout << endl;
    }
}

void testConfiguracion() {
    vector<int> paradasMaximoIteraciones = {100};
    vector<int> paradasIteracionesSinMejora = {10, 35, 50, 70};
    vector<int> profundidadesEleccionVertice = {1, 2, 4};
    vector<int> profundidadesEleccionConjunto = {1, 2, 4};
    ofstream logFile("testConfiguracion-log.txt");
    ofstream histProfFile("histograma-rcl.txt");
    ofstream graficosFile("resultadosTestConfiguracion.txt");
    vector<vector<vector<double>>> resultadosParaMaximoIteraciones(paradasMaximoIteraciones.size(), vector<vector<double>>(profundidadesEleccionVertice.size(), vector<double>(profundidadesEleccionConjunto.size())));
    vector<vector<vector<double>>> resultadosParaIteracionesSinMejora(paradasIteracionesSinMejora.size(), vector<vector<double>>(profundidadesEleccionVertice.size(), vector<double>(profundidadesEleccionConjunto.size())));
    vector<vector<vector<double>>> totalResultadosParaMaximoIteraciones(paradasMaximoIteraciones.size(), vector<vector<double>>(profundidadesEleccionVertice.size(), vector<double>(profundidadesEleccionConjunto.size())));
    vector<vector<vector<double>>> totalResultadosParaIteracionesSinMejora(paradasIteracionesSinMejora.size(), vector<vector<double>>(profundidadesEleccionVertice.size(), vector<double>(profundidadesEleccionConjunto.size())));
    int ganadasPorMaximo = 0, ganadasPorSinMejora = 0;
    vector<vector<int>> ganadasProfundidad(profundidadesEleccionVertice.size(), vector<int>(profundidadesEleccionConjunto.size()));
    logFile << "Corriendo test de configuracion optima de GRASP . . ." << endl;
    for (int cantVertices = MIN_VERTICES; cantVertices <= MAX_VERTICES; cantVertices++) {
        graficosFile << cantVertices << " ";
        for (int instancia = 1; instancia <= CANT_INSTANCIAS; instancia++) {
            int n, m, k, u, v;
            double w;
            std::cin >> n >> m >> k;
            Grafo g(n);
            for (int i = 0; i < m; i++) {
                std::cin >> u >> v >> w;
                g.setPesoArista(u - 1, v - 1, w);
            }
            Heuristica h(g,k);
            for (int maxIter = 0; maxIter < paradasMaximoIteraciones.size(); maxIter++) {
                for (int profVert = 0; profVert < profundidadesEleccionVertice.size(); profVert++) {
                    for (int profConj = 0; profConj < profundidadesEleccionConjunto.size(); profConj++) {
                        Grasp grasp(h);
                        grasp.setParadaMaximoIteraciones(paradasMaximoIteraciones[maxIter]);
                        grasp.setProfundidadEleccionVertice(profundidadesEleccionVertice[profVert]);
                        grasp.setProfundidadEleccionConjunto(profundidadesEleccionConjunto[profConj]);
                        double peso = grasp.ejecutar(Grasp::pararPorMaximoIteraciones);
                        resultadosParaMaximoIteraciones[maxIter][profVert][profConj] += peso;
                        totalResultadosParaMaximoIteraciones[maxIter][profVert][profConj] += peso;
                    }
                }
            }
            for (int iterSinM = 0; iterSinM < paradasIteracionesSinMejora.size(); iterSinM++) {
                for (int profVert = 0; profVert < profundidadesEleccionVertice.size(); profVert++) {
                    for (int profConj = 0; profConj < profundidadesEleccionConjunto.size(); profConj++) {
                        Grasp grasp(h);
                        grasp.setParadaIteracionesSinMejora(paradasIteracionesSinMejora[iterSinM]);
                        grasp.setProfundidadEleccionVertice(profundidadesEleccionVertice[profVert]);
                        grasp.setProfundidadEleccionConjunto(profundidadesEleccionConjunto[profConj]);
                        double peso = grasp.ejecutar(Grasp::pararPorIteracionesSinMejora);
                        resultadosParaIteracionesSinMejora[iterSinM][profVert][profConj] += peso;
                        totalResultadosParaIteracionesSinMejora[iterSinM][profVert][profConj] += peso;
                    }
                }
            }
        }
        // Ahora buscamos la mejor configuracion, es decir, la que dio menor peso total:
        bool esMejorIteracionesSinMejora = true;
        int mejorParada = -1, mejorProfVertice = -1, mejorProfConjunto = -1, indiceMejorProfVert = -1, indiceMejorProfConj = -1;
        double mejorPeso = DBL_MAX;
        for (int iterSinM = 0; iterSinM < paradasIteracionesSinMejora.size(); iterSinM++) {
            for (int profVert = profundidadesEleccionVertice.size() - 1; profVert >= 0; profVert--) {
                for (int profConj = profundidadesEleccionConjunto.size() - 1; profConj >= 0 ; profConj--) {
                    if (resultadosParaIteracionesSinMejora[iterSinM][profVert][profConj] < mejorPeso) {
                        mejorParada = paradasIteracionesSinMejora[iterSinM];
                        mejorProfVertice = profundidadesEleccionVertice[profVert];
                        mejorProfConjunto = profundidadesEleccionConjunto[profConj];
                        mejorPeso = resultadosParaIteracionesSinMejora[iterSinM][profVert][profConj];
                        indiceMejorProfVert = profVert;
                        indiceMejorProfConj = profConj;
                    }
                }
            }
        }
        for (int maxIter = 0; maxIter < paradasMaximoIteraciones.size(); maxIter++) {
            for (int profVert = profundidadesEleccionVertice.size() - 1; profVert >= 0; profVert--) {
                for (int profConj = profundidadesEleccionConjunto.size() - 1; profConj >= 0 ; profConj--) {
                    if (resultadosParaMaximoIteraciones[maxIter][profVert][profConj] < mejorPeso) {
                        esMejorIteracionesSinMejora = false;
                        mejorParada = paradasMaximoIteraciones[maxIter];
                        mejorProfVertice = profundidadesEleccionVertice[profVert];
                        mejorProfConjunto = profundidadesEleccionConjunto[profConj];
                        mejorPeso = resultadosParaMaximoIteraciones[maxIter][profVert][profConj];
                        indiceMejorProfVert = profVert;
                        indiceMejorProfConj = profConj;
                    }
                }
            }
        }
        ganadasProfundidad[indiceMejorProfVert][indiceMejorProfConj]++;
        if (esMejorIteracionesSinMejora) 
            ganadasPorSinMejora++; 
        else 
            ganadasPorMaximo++;
        logFile << endl << "Mejor configuracion para grafos con n = " << cantVertices << ":" << endl;
        logFile << "Es mejor parar por " << (esMejorIteracionesSinMejora ? "iteraciones sin mejora" : "maximo de iteraciones") << "." << endl;
        logFile << "Limite de iteraciones = " << mejorParada << endl;
        logFile << "Profundidad de eleccion de vertices = " << mejorProfVertice << endl;
        logFile << "Profundidad de eleccion de conjuntos = " << mejorProfConjunto << endl;
        resultadosParaMaximoIteraciones = vector<vector<vector<double>>>(paradasMaximoIteraciones.size(), vector<vector<double>>(profundidadesEleccionVertice.size(), vector<double>(profundidadesEleccionConjunto.size())));;
        resultadosParaIteracionesSinMejora = vector<vector<vector<double>>>(paradasIteracionesSinMejora.size(), vector<vector<double>>(profundidadesEleccionVertice.size(), vector<double>(profundidadesEleccionConjunto.size())));;
        // Esto imprime: cantVertices limiteIteracionesGanadora mejorProfVertice|mejorProfConjunto indiceProfundidadParaGraficar
        graficosFile << mejorParada << " " << mejorProfVertice << mejorProfConjunto;
        graficosFile << " " << indiceMejorProfVert * profundidadesEleccionVertice.size() + indiceMejorProfConj + 1 << endl;
    }
    bool esMejorIteracionesSinMejora = true;
    int mejorParada = -1, mejorProfVertice = -1, mejorProfConjunto = -1;
    double mejorPeso = DBL_MAX;
    logFile << endl << "Resultados" << endl;
    logFile <<         "==========" << endl << endl;
    for (int iterSinM = 0; iterSinM < paradasIteracionesSinMejora.size(); iterSinM++) {
        for (int profVert = profundidadesEleccionVertice.size() - 1; profVert >= 0; profVert--) {
            for (int profConj = profundidadesEleccionConjunto.size() - 1; profConj >= 0 ; profConj--) {
                logFile << "Iteraciones sin mejora con limite = " << paradasIteracionesSinMejora[iterSinM] << ", prof. vert. = " << profundidadesEleccionVertice[profVert] << ", prof. conj. = " << profundidadesEleccionConjunto[profConj] << ". Peso total = " << fixed << totalResultadosParaIteracionesSinMejora[iterSinM][profVert][profConj] << endl;
                if (totalResultadosParaIteracionesSinMejora[iterSinM][profVert][profConj] < mejorPeso) {
                    mejorParada = paradasIteracionesSinMejora[iterSinM];
                    mejorProfVertice = profundidadesEleccionVertice[profVert];
                    mejorProfConjunto = profundidadesEleccionConjunto[profConj];
                    mejorPeso = totalResultadosParaIteracionesSinMejora[iterSinM][profVert][profConj];
                }
            }
        }
    }
    for (int maxIter = 0; maxIter < paradasMaximoIteraciones.size(); maxIter++) {
        for (int profVert = profundidadesEleccionVertice.size() - 1; profVert >= 0; profVert--) {
            for (int profConj = profundidadesEleccionConjunto.size() - 1; profConj >= 0 ; profConj--) {
                logFile << "Maximo de iteraciones con limite  = " << paradasMaximoIteraciones[maxIter] << ", prof. vert. = " << profundidadesEleccionVertice[profVert] << ", prof. conj. = " << profundidadesEleccionConjunto[profConj] << ". Peso total = " << fixed << totalResultadosParaMaximoIteraciones[maxIter][profVert][profConj] << endl;
                if (totalResultadosParaMaximoIteraciones[maxIter][profVert][profConj] < mejorPeso) {
                    esMejorIteracionesSinMejora = false;
                    mejorParada = paradasMaximoIteraciones[maxIter];
                    mejorProfVertice = profundidadesEleccionVertice[profVert];
                    mejorProfConjunto = profundidadesEleccionConjunto[profConj];
                    mejorPeso = totalResultadosParaMaximoIteraciones[maxIter][profVert][profConj];
                }
            }
        }
    }
    //cout.precision(4);
    logFile << endl << "Parar por maximo de iteraciones gano " << ganadasPorMaximo << " veces." << endl;
    logFile << "Parar por iteraciones sin mejora gano " << ganadasPorSinMejora << " veces." << endl;
    for (int i = 0; i < ganadasProfundidad.size(); i++) {
        for (int j = 0; j < ganadasProfundidad[i].size(); j++) {
            histProfFile << "(" << profundidadesEleccionVertice[i] << "," << profundidadesEleccionConjunto[j] << ")" << " " << ganadasProfundidad[i][j] << endl;
            logFile << "La combinacion de profundidades de eleccion vertice-conjunto " << profundidadesEleccionVertice[i] << " " << profundidadesEleccionConjunto[j] << " gano " << ganadasProfundidad[i][j] << " veces." << endl;
        }
    }
    logFile << endl << "Mejor configuracion general para el total del conjunto de instancias (es decir, la configuracion que dio menor peso para la suma de todas las instancias):" << endl;
    logFile << "Es mejor parar por " << (esMejorIteracionesSinMejora ? "iteraciones sin mejora" : "maximo de iteraciones") << "." << endl;
    logFile << "Limite de iteraciones = " << mejorParada << endl;
    logFile << "Profundidad de eleccion de vertices = " << mejorProfVertice << endl;
    logFile << "Profundidad de eleccion de conjuntos = " << mejorProfConjunto << endl;
    logFile.close();
    histProfFile.close();
    graficosFile.close();
}

void testTiempoEjecucionGrasp() {
    vector<int> paradasMaximoIteraciones = {100};
    vector<int> paradasIteracionesSinMejora = {70};
    vector<int> profundidadesRCL = {2, 4}; // Esto pone profundidad vertice-conjunto en (2,2) o en (4,4)
    for (int cantVertices = MIN_VERTICES; cantVertices <= MAX_VERTICES; cantVertices++) {
        cout << cantVertices << " ";
        vector<vector<int>> tiemposMaximo = vector<vector<int>>(paradasMaximoIteraciones.size(), vector<int>(profundidadesRCL.size()));
        vector<vector<int>> tiemposSinMejora = vector<vector<int>>(paradasIteracionesSinMejora.size(), vector<int>(profundidadesRCL.size()));
        for (int instancia = 1; instancia <= CANT_INSTANCIAS; instancia++) {
            int n, m, k, u, v;
            double w;
            std::cin >> n >> m >> k;
            Grafo g(n);
            for (int i = 0; i < m; i++) {
                std::cin >> u >> v >> w;
                g.setPesoArista(u - 1, v - 1, w);
            }
            Heuristica h(g,k);
            for (int maxIter = 0; maxIter < paradasMaximoIteraciones.size(); maxIter++) {
                for (int profRCL = 0; profRCL < profundidadesRCL.size(); profRCL++) {
                    Grasp grasp(h);
                    grasp.setParadaMaximoIteraciones(paradasMaximoIteraciones[maxIter]);
                    grasp.setProfundidadEleccionVertice(profundidadesRCL[profRCL]);
                    grasp.setProfundidadEleccionConjunto(profundidadesRCL[profRCL]);
                    chrono::microseconds minTiempo(INT_MAX);
                    for (int rep = 1; rep <= CANT_REPETICIONES_CALCULO_INSTANCIA; rep++) {
                        auto start_time = std::chrono::high_resolution_clock::now();
                        grasp.ejecutar(Grasp::pararPorMaximoIteraciones);
                        auto end_time = std::chrono::high_resolution_clock::now();
                        auto tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
                        if (tiempoRep < minTiempo)
                            minTiempo = tiempoRep;
                    }
                    tiemposMaximo[maxIter][profRCL] += minTiempo.count();
                }
            }
            for (int iterSinM = 0; iterSinM < paradasIteracionesSinMejora.size(); iterSinM++) {
                for (int profRCL = 0; profRCL < profundidadesRCL.size(); profRCL++) {
                    Grasp grasp(h);
                    grasp.setParadaIteracionesSinMejora(paradasIteracionesSinMejora[iterSinM]);
                    grasp.setProfundidadEleccionVertice(profundidadesRCL[profRCL]);
                    grasp.setProfundidadEleccionConjunto(profundidadesRCL[profRCL]);
                    chrono::microseconds minTiempo(INT_MAX);
                    for (int rep = 1; rep <= CANT_REPETICIONES_CALCULO_INSTANCIA; rep++) {
                        auto start_time = std::chrono::high_resolution_clock::now();
                        grasp.ejecutar(Grasp::pararPorIteracionesSinMejora);
                        auto end_time = std::chrono::high_resolution_clock::now();
                        auto tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
                        if (tiempoRep < minTiempo)
                            minTiempo = tiempoRep;
                    }
                    tiemposSinMejora[iterSinM][profRCL] += minTiempo.count();
                }
            }
        }
        for (auto & i : tiemposMaximo) {
            for (auto & j : i) {
                j /= CANT_INSTANCIAS;
                cout << j << " ";
            }
        }
        for (auto & i : tiemposSinMejora) {
            for (auto & j : i) {
                j /= CANT_INSTANCIAS;
                cout << j << " ";
            }
        }
        cout << endl;
    }
}

void busquedaLocalUnNodo(Heuristica & h, vector<set<int>> particion, double & pesoParticion) {
    int k = h.getK();
    int n = h.getGrafo().getCantidadVertices();
    vector<int> node_indexed_partition(n, 0);
    for ( int i = 0; i < k; i++) {
        for (auto & v : particion[i]) {
            node_indexed_partition[v] = i;
        }
    }
    bool has_improved = true;
    while (has_improved) {
        has_improved = false;
        for (int i = 0; i < n; ++i) {
            double node_weight_in_current_subset = h.pesoEnSubconjunto(i, particion[node_indexed_partition[i]]);
            bool swapped = false;
            int subset = 0;
            while (!swapped && subset < k) {
                if (subset != node_indexed_partition[i]) {
                    double node_weight_in_subset_j = h.pesoEnSubconjunto(i, particion[subset]);
                    if (node_weight_in_current_subset > node_weight_in_subset_j) {
                        particion[node_indexed_partition[i]].erase(i);
                        particion[subset].insert(i);
                        node_indexed_partition[i] = subset;
                        pesoParticion = pesoParticion - node_weight_in_current_subset + node_weight_in_subset_j;
                        has_improved = true;
                        swapped = true;
                    }
                }
                ++subset;
            }
        }
    }
}

void testsEjercicioSeis() {
    int profVert = 4;
    int profConj = 4;
    //vector<int> maximoIteraciones = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    const int limiteIteraciones = 70;
    double totalPesosExacto = 0.0;
    double totalPesosGreedyPura = 0.0;
    double totalPesosGreedyMasLocal = 0.0;
    double totalPesosGRASP = 0.0;
    int totalTiemposExacto = 0.0;
    int totalTiemposGreedyPura = 0.0;
    int totalTiemposGreedyMasLocal = 0.0;
    int totalTiemposGRASP = 0.0;
    
    for (int cantVertices = MIN_VERTICES; cantVertices <= MAX_VERTICES; cantVertices++) {
        totalPesosExacto = 0.0;
        totalPesosGreedyPura = 0.0;
        totalPesosGreedyMasLocal = 0.0;
        totalPesosGRASP = 0.0;
        totalTiemposExacto = 0.0;
        totalTiemposGreedyPura = 0.0;
        totalTiemposGreedyMasLocal = 0.0;
        totalTiemposGRASP = 0.0;
        
        cout << cantVertices << " ";
        
        for (int instancia = 1; instancia <= CANT_INSTANCIAS; instancia++) {
            int n, m, k, u, v;
            double w;
            std::cin >> n >> m >> k;
            Grafo g(n);
            vector<vector<double>> adym(n, vector<double> (n, 0));
            for (int i = 0; i < m; i++) {
                std::cin >> u >> v >> w;
                g.setPesoArista(u - 1, v - 1, w);
                adym[u - 1][v - 1] = w;
                adym[v - 1][u - 1] = w;
            }
            
            // Calculo de tiempo de ejecucion y peso del algoritmo exacto:
            if (cantVertices <= EXACTO_MAX_VERTICES) {
                double pesoExacto;
                chrono::microseconds minTiempo(INT_MAX);
                for (int rep = 1; rep <= CANT_REPETICIONES_CALCULO_INSTANCIA; rep++) {
                    auto start_time = std::chrono::high_resolution_clock::now();
                    pesoExacto = algoritmo_exacto(adym, k);
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
                    if (tiempoRep < minTiempo)
                        minTiempo = tiempoRep;
                }
                totalTiemposExacto += minTiempo.count();
                totalPesosExacto += pesoExacto;
            }
            
            // Calculo de tiempo de ejecucion y peso de la heuristica golosa constructiva:
            Heuristica h(g,k);
            {
                double pesoGolosaPura;
                chrono::microseconds minTiempo(INT_MAX);
                for (int rep = 1; rep <= CANT_REPETICIONES_CALCULO_INSTANCIA; rep++) {
                    auto start_time = std::chrono::high_resolution_clock::now();
                    vector<set<int>> solucionGolosaPura = h.resolverGolosoPuro();
                    pesoGolosaPura = pesoParticion(h.getGrafo(), solucionGolosaPura);
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
                    if (tiempoRep < minTiempo)
                        minTiempo = tiempoRep;
                }
                totalTiemposGreedyPura += minTiempo.count();
                totalPesosGreedyPura += pesoGolosaPura;
            }
            
            // Calculo de tiempo de ejecucion y peso de golosa + busqueda local:
            {
                double pesoGolosaMasLocal;
                chrono::microseconds minTiempo(INT_MAX);
                for (int rep = 1; rep <= CANT_REPETICIONES_CALCULO_INSTANCIA; rep++) {
                    auto start_time = std::chrono::high_resolution_clock::now();
                    vector<set<int>> solucionGolosaPura = h.resolverGolosoPuro();
                    double peso = pesoParticion(h.getGrafo(), solucionGolosaPura);
                    busquedaLocalUnNodo(h, solucionGolosaPura, peso);
                    pesoGolosaMasLocal = peso;
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
                    if (tiempoRep < minTiempo)
                        minTiempo = tiempoRep;
                }
                totalTiemposGreedyMasLocal += minTiempo.count();
                totalPesosGreedyMasLocal += pesoGolosaMasLocal;
            }
            
            // Calculo de tiempo de ejecucion y peso de GRASP:
            {
                double pesoGRASP;
                chrono::microseconds minTiempo(INT_MAX);
                for (int rep = 1; rep <= CANT_REPETICIONES_CALCULO_INSTANCIA; rep++) {
                    auto start_time = std::chrono::high_resolution_clock::now();
                    Grasp grasp(h);
                    grasp.setParadaIteracionesSinMejora(limiteIteraciones);
                    grasp.setProfundidadEleccionVertice(profVert);
                    grasp.setProfundidadEleccionConjunto(profConj);
                    pesoGRASP = grasp.ejecutar(Grasp::pararPorIteracionesSinMejora);
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
                    if (tiempoRep < minTiempo)
                        minTiempo = tiempoRep;
                }
                totalTiemposGRASP += minTiempo.count();
                totalPesosGRASP += pesoGRASP;
            }
        }
        cout << fixed << totalPesosExacto << " " << totalPesosGreedyPura << " " << totalPesosGreedyMasLocal << " " << totalPesosGRASP << " " << totalTiemposExacto << " " << totalTiemposGreedyPura << " " << totalTiemposGreedyMasLocal << " " << totalTiemposGRASP << endl;
    }
}

int main(int argc, char* argv[]) {
    std::ifstream archivoConfiguracion("../configuracionGeneracionInstancias.txt");
    archivoConfiguracion >> CANT_INSTANCIAS >> MIN_VERTICES >> MAX_VERTICES;
    archivoConfiguracion.close();
    srand(time(NULL));
    cout.precision(4);

    //testConfiguracion();
    //testTiempoEjecucionGrasp();
    //testCalidadVsExacto(MAX_VERTICES);
    testsEjercicioSeis();
    
    return 0;
}
