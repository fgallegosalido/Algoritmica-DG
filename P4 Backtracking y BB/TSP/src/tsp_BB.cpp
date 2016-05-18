#include "grafo.h"

int* Graph::TSPConBB(double &tam){
  int *tour = insertion(tam);   // Aproximación Greedy mediante el algoritmo de inserción

  return tour;
}
