#include "grasp.h"
#include <iostream>

void Grasp::busquedaLocalUnNodo() {
  int k = h_.getK();
  int n = h_.getGrafo().getCantidadVertices();
  //cout << "Starting with a total weight of " << pesoParticionActual_ << endl;
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
      float node_weight_in_current_subset = h_.pesoEnSubconjunto(i, particionActual_[node_indexed_partition[i]]);
      bool swapped = false;
      int subset = 0;
      while (!swapped && subset < k) {
        if (subset != node_indexed_partition[i]) {
          //cout << "Considering swapping node " << i << " from subset " << node_indexed_partition[i] << " to subset " << subset << endl;
          float node_weight_in_subset_j = h_.pesoEnSubconjunto(i, particionActual_[subset]);
          if (node_weight_in_current_subset > node_weight_in_subset_j) {
            //cout << "FOUND IMPROVEMENT!" << endl;
            //cout << " Swapping node " << i << " from subset " << node_indexed_partition[i] << " to subset " << subset << endl;
            particionActual_[node_indexed_partition[i]].erase(i);
            particionActual_[subset].insert(i);
            node_indexed_partition[i] = subset;
            pesoParticionActual_ = pesoParticionActual_ - node_weight_in_current_subset + node_weight_in_subset_j;
            //cout << "New total weight is: " << pesoParticionActual_ << endl;
            has_improved = true;
            swapped = true;
          }
        }
        ++subset;
      }
    }
  }

  //cout << "Minimum weight reached: " << pesoParticionActual_ << endl;
  //cout << "PARTITION" << endl;
  //for (int i = 0; i < k; ++i) {
    //cout << "Partition " << i << ": ";
    //for(set<int>::iterator it = particionActual_[i].begin(); it != particionActual_[i].end(); ++it) {
      //cout << *it << ' ';
    //}
    //cout << endl;
  //}
}

Grasp::Grasp(Heuristica h) : h_(h), particionActual_(h_.getK()), mejorParticion_(h_.getK()) {
    int n = h_.getGrafo().getCantidadVertices();
    for (int i = 0; i < n; i++) {
        particionActual_[0].insert(i);
        mejorParticion_[0].insert(i);
    }
    pesoParticionActual_ = pesoParticion(particionActual_);
    pesoMejorParticion_ = pesoParticionActual_;
}

Grasp::~Grasp() {
    
}

bool Grasp::parar(int criterio) {
    switch (criterio) {
        case Grasp::pararPorMaximoIteraciones:
            return iteracionActual_ >= paradaMaximoIteraciones_; 
        case Grasp::pararPorIteracionesSinMejora:
            return (iteracionActual_ - ultimaIteracionConMejora_ >= paradaIteracionesSinMejora_);
        case Grasp::pararPorMaximoYPorSinMejora:
            return ( (iteracionActual_ >= paradaMaximoIteraciones_) || ( (iteracionActual_ - ultimaIteracionConMejora_) >= paradaIteracionesSinMejora_) );
        default:
            return true;
    }
}

float Grasp::pesoParticion(const vector<set<int>> & particion) {
    float res = 0;
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

void Grasp::ejecutar(int criterioParada) {
    cout.precision(2);
    cout << "Peso total del grafo: " << fixed << pesoParticionActual_ << endl;
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
    cout << "Ultima iteracion: " << iteracionActual_ << endl;
    cout << "Mejor peso: " << fixed << pesoMejorParticion_ << endl;
}

