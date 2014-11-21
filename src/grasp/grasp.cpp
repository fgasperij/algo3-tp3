#include "grasp.h"
#include <iostream>

Grasp::Grasp(Heuristica h) : h_(h), particionActual_(h_.getK()), mejorParticion_(h_.getK()) {
    int n = h_.getGrafo().getCantidadVertices();
    for (int i = 0; i < n; i++) {
        particionActual_[0].insert(i);
        mejorParticion_[0].insert(i);
    }
    pesoParticionActual_ = pesoParticion(particionActual_);
    pesoMejorParticion_ = pesoParticionActual_;
}

void Grasp::busquedaLocalUnNodo() {
    int k = h_.getK();
    int n = h_.getGrafo().getCantidadVertices();
    vector<int> node_indexed_partition(n, 0);
    for ( int i = 0; i < k; i++) {
        for (auto & v : particionActual_[i]) {
            node_indexed_partition[v] = i;
        }
    }
    bool has_improved = true;
    while (has_improved) {
        has_improved = false;
        for (int i = 0; i < n; ++i) {
            double node_weight_in_current_subset = h_.pesoEnSubconjunto(i, particionActual_[node_indexed_partition[i]]);
            bool swapped = false;
            int subset = 0;
            while (!swapped && subset < k) {
                if (subset != node_indexed_partition[i]) {
                    double node_weight_in_subset_j = h_.pesoEnSubconjunto(i, particionActual_[subset]);
                    if (node_weight_in_current_subset > node_weight_in_subset_j) {
                        particionActual_[node_indexed_partition[i]].erase(i);
                        particionActual_[subset].insert(i);
                        node_indexed_partition[i] = subset;
                        pesoParticionActual_ = pesoParticionActual_ - node_weight_in_current_subset + node_weight_in_subset_j;
                        has_improved = true;
                        swapped = true;
                    }
                }
                ++subset;
            }
        }
    }
}

bool Grasp::parar(int criterio) {
    switch (criterio) {
        case Grasp::pararPorMaximoIteraciones:
            return iteracionActual_ >= paradaMaximoIteraciones_; 
        case Grasp::pararPorIteracionesSinMejora:
            return (iteracionActual_ - ultimaIteracionConMejora_) >= paradaIteracionesSinMejora_;
        case Grasp::pararPorMaximoYPorSinMejora:
            return (iteracionActual_ >= paradaMaximoIteraciones_) || ( (iteracionActual_ - ultimaIteracionConMejora_) >= paradaIteracionesSinMejora_);
        default:
            return true;
    }
}

double Grasp::pesoParticion(const vector<set<int>> & particion) {
    double res = 0;
    for (auto & conjunto : particion) {
        for (auto i = conjunto.begin(); i != conjunto.end(); i++) {
            int v = *i;
            auto j = i;
            j++;
            while (j != conjunto.end()) {
                res += h_.getGrafo().getPesoArista(v, *j);
                j++;
            }
        }
    }
    return res;
}

void Grasp::setParadaMaximoIteraciones(int paradaMaximoIteraciones) {
    paradaMaximoIteraciones_ = paradaMaximoIteraciones;
}

void Grasp::setParadaIteracionesSinMejora(int paradaIteracionesSinMejora) {
    paradaIteracionesSinMejora_ = paradaIteracionesSinMejora;
}

void Grasp::setProfundidadEleccionVertice(int profundidadEleccionVertice) {
    h_.setProfundidadEleccionVertice(profundidadEleccionVertice);
}

void Grasp::setProfundidadEleccionConjunto(int profundidadEleccionConjunto) {
    h_.setProfundidadEleccionConjunto(profundidadEleccionConjunto);
}

vector<set<int>> Grasp::getMejorParticion() {
    return mejorParticion_;
}

double Grasp::ejecutar(int criterioParada) { // Ejecuta GRASP hasta que se llegue al criterio de parada y devuelve el minimo peso
    cout.precision(4);
    iteracionActual_ = 0;
    ultimaIteracionConMejora_ = 0;
    while( ! parar(criterioParada) ) {
        iteracionActual_++;
        particionActual_ = h_.resolver();
        pesoParticionActual_ = pesoParticion(particionActual_);
        busquedaLocalUnNodo();
        if (pesoParticionActual_ < pesoMejorParticion_) {
            mejorParticion_ = particionActual_;
            pesoMejorParticion_ = pesoParticionActual_;
            ultimaIteracionConMejora_ = iteracionActual_;
        }
    }
    return pesoMejorParticion_;
}

void Grasp::imprimirParticion(const std::vector<std::set<int>> & particion, int n) {
    std::vector<int> conjuntoPorVertice(n);
    int k = particion.size();
    for ( int i = 0; i < k; i++) {
        for (auto & v : particion[i]) {
            conjuntoPorVertice[v] = i;
        }
    }
    for (auto & conj : conjuntoPorVertice) {
        std::cout << conj + 1 << " ";
    }
    std::cout << std::endl;
}

