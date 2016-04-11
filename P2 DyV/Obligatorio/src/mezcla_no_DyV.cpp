#include <iostream>
#include <fstream>
using namespace std;

/*
Función que calcula el mínimo de entre los elementos apuntados por los índices
*/
int f_pos_min(int* vec_indices, int** M, int num_vec){
  int pos_min = 0;
  while((vec_indices[pos_min] <0) && (pos_min < num_vec))
    ++pos_min;
  for (int i=pos_min+1; i<num_vec; ++i){
    if (vec_indices[i] >= 0){
      if (M[i][vec_indices[i]] < M[pos_min][vec_indices[pos_min]])
        pos_min = i;
    }
  }
  return pos_min;
}

int* mezcla_no_DyV(int** M, int num_vec, int num_elem){
  int* vec_indices = new int[num_vec]; //Vector que almacena los índices
  for (int i=0; i<num_vec; ++i)
    vec_indices[i]=0;

  int pos_escritas = 0; //Número de posiciones escritas
  const int MAX_POS_ESCRITAS = num_vec*num_elem; //Tope de las posiciones que se pueden escribir (n*k)
  int* vec_ordenado = new int[MAX_POS_ESCRITAS]; //Variable donde se va almacenando el vector resultante ordenado.

  while (pos_escritas < MAX_POS_ESCRITAS){
    int pos_min = f_pos_min(vec_indices, M, num_vec);
    vec_ordenado[pos_escritas] = M[pos_min][vec_indices[pos_min]];
    if (vec_indices[pos_min] >= num_elem-1)
      vec_indices[pos_min] = -1;
    else
      ++vec_indices[pos_min];
    ++pos_escritas;
  }

  delete[] vec_indices;
  return vec_ordenado;
}
