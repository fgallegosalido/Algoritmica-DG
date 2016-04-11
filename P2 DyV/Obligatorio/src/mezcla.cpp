#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <fstream>
#include <chrono>
#include "mergekvectores.cpp"
#include "mezcla_no_DyV.cpp"
//#include <algorithm>
//#include <vector>
using namespace std;

//generador de ejemplor para el problema de mezcla de k vectores ordenados.
//Para obtener k vectores ordenados de forma creciente cada uno con n elementos,
//genera un vector de tamaño k*n con todos los enteros entre 0 y kn-1 ordenados.
//Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de
//tamaño n para obtener los k vectores. Están ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme(){ //Genera un número uniformemente distribuido en el
                   //intervalo [0,1) a partir de uno de los generadores
                   //disponibles en C.
  int t = rand();
  double f = ((double)RAND_MAX+1.0);
  return (double)t/f;
}

int main(int argc, char * argv[]){

  if (argc != 3){
    cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
    return -1;
  }

  int n = atoi(argv[1]);
  int k=atoi(argv[2]);
  int **T;
  T =  new int * [k];
  assert(T);

  for (int i = 0; i < k; i++)
    T[i]= new int [n];

  int N=k*n;
  int * aux = new int[N];
  assert(aux);

  srand(time(0));
  //genero todos los enteros entre 0 y k*n-1
  for (int j=0; j<N; j++) aux[j]=j;

  //para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
  for (int i=0; i<k; i++) {
    int t=0;
    int m=0;
    while (m<n) {
      double u=uniforme();

      if ((N-t)*u >= (n-m)) t++;
      else {
        T[i][m]=aux[t];
        t++;
        m++;
      }
    }
  }
  int* ordenado;

  chrono::high_resolution_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido, transcurrido2;
  tantes = chrono::high_resolution_clock::now();

  ordenado = MergeVectors(T, k, n);

  tdespues = chrono::high_resolution_clock::now();
  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);


  // merge
  int **M;
  M =  new int * [k];
  assert(M);

  for (int i = 0; i < k; i++)
    M[i]= new int [n];

  for (int i=0; i<k; i++) 
    for (int j=0; j<n; j++)
      M[i][j] = T[i][j];


  int* ordenado_merge;
  tantes = chrono::high_resolution_clock::now();

  ordenado_merge = mezcla_no_DyV(M, k, n);

  tdespues = chrono::high_resolution_clock::now();
  transcurrido2 = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);


// Impresion
  ofstream fuerza_bruta("fuerza_bruta.dat"), dyv("dyv.dat");
    
  fuerza_bruta << k << " " << n << " " <<  transcurrido.count();
  dyv << k << " " << n << " " << transcurrido2.count();       
  
  fuerza_bruta.close();
  dyv.close();
  delete [] aux;
}
