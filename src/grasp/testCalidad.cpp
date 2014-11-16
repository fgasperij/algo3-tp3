#include "grasp.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <cfloat>

using namespace std;

float algoritmo_exacto(const vector<vector<float>> & adym, int k);

int CANT_INSTANCIAS;
int MIN_VERTICES;
int MAX_VERTICES;

void testCalidadVsExacto(int max_vertices) { // Requiere max_vertices <= MAX_VERTICES
    for (int cantVertices = MIN_VERTICES; cantVertices <= max_vertices; cantVertices++) {
        cout << cantVertices << " ";
        float promedio = 0.0;
        for (int instancia = 1; instancia <= CANT_INSTANCIAS; instancia++) {
            int n, m, k, u, v;
            float w;
            std::cin >> n >> m >> k;
            Grafo g(n);
            vector<vector<float>> adym(n, vector<float> (n, 0));
            for (int i = 0; i < m; i++) {
                std::cin >> u >> v >> w;
                g.setPesoArista(u - 1, v - 1, w);
                adym[u - 1][v - 1] = w;
                adym[v - 1][u - 1] = w;
            }
            float pesoExacto = algoritmo_exacto(adym, k);
            if (pesoExacto < 0.0001) {
                pesoExacto = 0.0001; // Para evitar divisiones por cero al hacer pesoGrasp / pesoExacto
            }
            Heuristica h(g,k);
            Grasp grasp(h);
            grasp.setParadaIteracionesSinMejora(70);
            grasp.setProfundidadEleccionConjunto(4);
            grasp.setProfundidadEleccionVertice(4);
            float pesoGrasp = grasp.ejecutar(Grasp::pararPorIteracionesSinMejora);
            if (pesoGrasp < 0.0001) {
                pesoGrasp = 0.0001; // Si fueran ambos pesos 0.0, con esto me aseguro que pesoGrasp / pesoExacto = 1.0
            }
            promedio += abs(100.f * pesoGrasp / pesoExacto - 100.f); // Qué tanto más pesada es la solución de la GRASP en relación a la solución óptima, en porcentaje (si pesoGrasp fuera el doble que pesoExacto, daría 100%)
            //promedio += (pesoGrasp - pesoExacto);
        }
        promedio /= CANT_INSTANCIAS;
        cout << fixed << promedio << endl;
    }
}

void testConfiguracion() {
    vector<int> paradasMaximoIteraciones = {100};
    vector<int> paradasIteracionesSinMejora = {10, 35, 50, 70};
    vector<int> profundidadesEleccionVertice = {2, 4};
    vector<int> profundidadesEleccionConjunto = {2, 4};
    vector<vector<vector<float>>> resultadosParaMaximoIteraciones(4, vector<vector<float>>(4, vector<float>(4)));
    vector<vector<vector<float>>> resultadosParaIteracionesSinMejora(4, vector<vector<float>>(4, vector<float>(4)));
    vector<vector<vector<float>>> totalResultadosParaMaximoIteraciones(4, vector<vector<float>>(4, vector<float>(4)));
    vector<vector<vector<float>>> totalResultadosParaIteracionesSinMejora(4, vector<vector<float>>(4, vector<float>(4)));
    int ganadasPorMaximo = 0, ganadasPorSinMejora = 0;
    vector<vector<int>> ganadasProfundidad(profundidadesEleccionVertice.size(), vector<int>(profundidadesEleccionConjunto.size()));
    cout << "Corriendo test de configuracion optima de GRASP . . ." << endl;
    for (int cantVertices = MIN_VERTICES; cantVertices <= MAX_VERTICES; cantVertices++) {
        cout << cantVertices << " ";
        for (int instancia = 1; instancia <= CANT_INSTANCIAS; instancia++) {
            int n, m, k, u, v;
            float w;
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
                        resultadosParaMaximoIteraciones[maxIter][profVert][profConj] += grasp.ejecutar(Grasp::pararPorMaximoIteraciones);
                        totalResultadosParaMaximoIteraciones[maxIter][profVert][profConj] += grasp.ejecutar(Grasp::pararPorMaximoIteraciones);
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
                        resultadosParaIteracionesSinMejora[iterSinM][profVert][profConj] += grasp.ejecutar(Grasp::pararPorIteracionesSinMejora);
                        totalResultadosParaIteracionesSinMejora[iterSinM][profVert][profConj] += grasp.ejecutar(Grasp::pararPorIteracionesSinMejora);
                    }
                }
            }
        }
        // Ahora buscamos la mejor configuracion, es decir, la que dio menor peso total:
        bool esMejorIteracionesSinMejora = true;
        int mejorParada = -1, mejorProfVertice = -1, mejorProfConjunto = -1, indiceMejorProfVert = -1, indiceMejorProfConj = -1;
        float mejorPeso = FLT_MAX;
        for (int iterSinM = 0; iterSinM < paradasIteracionesSinMejora.size(); iterSinM++) {
            for (int profVert = 0; profVert < profundidadesEleccionVertice.size(); profVert++) {
                for (int profConj = 0; profConj < profundidadesEleccionConjunto.size(); profConj++) {
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
            for (int profVert = 0; profVert < profundidadesEleccionVertice.size(); profVert++) {
                for (int profConj = 0; profConj < profundidadesEleccionConjunto.size(); profConj++) {
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
        //cout << endl << "Mejor configuracion para grafos con n = " << cantVertices << ":" << endl;
        //cout << "Es mejor parar por " << (esMejorIteracionesSinMejora ? "iteraciones sin mejora" : "maximo de iteraciones") << "." << endl;
        //cout << "Limite de iteraciones = " << mejorParada << endl;
        //cout << "Profundidad de eleccion de vertices = " << mejorProfVertice << endl;
        //cout << "Profundidad de eleccion de conjuntos = " << mejorProfConjunto << endl;
        resultadosParaMaximoIteraciones = vector<vector<vector<float>>>(4, vector<vector<float>>(4, vector<float>(4)));
        resultadosParaIteracionesSinMejora = vector<vector<vector<float>>>(4, vector<vector<float>>(4, vector<float>(4)));
        cout << mejorParada << endl;
    }
    bool esMejorIteracionesSinMejora = true;
    int mejorParada = -1, mejorProfVertice = -1, mejorProfConjunto = -1;
    float mejorPeso = FLT_MAX;
    for (int iterSinM = 0; iterSinM < paradasIteracionesSinMejora.size(); iterSinM++) {
        for (int profVert = 0; profVert < profundidadesEleccionVertice.size(); profVert++) {
            for (int profConj = 0; profConj < profundidadesEleccionConjunto.size(); profConj++) {
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
        for (int profVert = 0; profVert < profundidadesEleccionVertice.size(); profVert++) {
            for (int profConj = 0; profConj < profundidadesEleccionConjunto.size(); profConj++) {
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
    int ganadoraTotalProfundidad = 0, indiceMejorProfVert = -1, indiceMejorProfConj = -1;
    for (int i = 0; i < ganadasProfundidad.size(); i++) {
        for (int j = 0; j < ganadasProfundidad.size(); j++) {
            if (ganadasProfundidad[i][j] > ganadoraTotalProfundidad) {
                indiceMejorProfVert = i;
                indiceMejorProfConj = j;
                ganadoraTotalProfundidad = ganadasProfundidad[i][j];
            }
        }
    }
    cout << endl;
    cout << "Parar por maximo de iteraciones gano " << ganadasPorMaximo << " veces." << endl;
    cout << "Parar por iteraciones sin mejora gano " << ganadasPorSinMejora << " veces." << endl;
    cout << "La combinacion de profundidades de eleccion vertice-conjunto que mas gano es " << profundidadesEleccionVertice[indiceMejorProfVert] << " " << profundidadesEleccionConjunto[indiceMejorProfConj] << endl;
    cout << endl << "Mejor configuracion general para el total del conjunto de instancias (es decir, la configuracion que dio menor peso para la suma de todas las instancias):" << endl;
    cout << "Es mejor parar por " << (esMejorIteracionesSinMejora ? "iteraciones sin mejora" : "maximo de iteraciones") << "." << endl;
    cout << "Limite de iteraciones = " << mejorParada << endl;
    cout << "Profundidad de eleccion de vertices = " << mejorProfVertice << endl;
    cout << "Profundidad de eleccion de conjuntos = " << mejorProfConjunto << endl;
}

int main(int argc, char* argv[]) {
    std::ifstream archivoConfiguracion("../configuracionGeneracionInstancias.txt");
    archivoConfiguracion >> CANT_INSTANCIAS >> MIN_VERTICES >> MAX_VERTICES;
    archivoConfiguracion.close();
    srand(time(NULL));
    cout.precision(4);
    
    int max_vertices = 20;
    //testConfiguracion();
    testCalidadVsExacto(max_vertices);
    
    return 0;
}
