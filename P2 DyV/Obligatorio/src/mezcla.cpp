#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <fstream>
#include <chrono>
#include "mezcla_DyV.cpp"
#include "mezcla_no_DyV.cpp"
//#include <algorithm>
//#include <vector>
using namespace std;

//generador de ejemplo para el problema de mezcla de k vectores ordenados.
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

  if (argc != 4){
    cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << " <mode>" << endl;
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
  int* ordenado_dyv;

  chrono::high_resolution_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido, transcurrido2;
  tantes = chrono::high_resolution_clock::now();

  ordenado_dyv = MezclaDyV(T, k, n);

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


  int* ordenado_no_dyv;
  tantes = chrono::high_resolution_clock::now();

  ordenado_no_dyv = MezclaNoDyV(M, k, n);

  tdespues = chrono::high_resolution_clock::now();
  transcurrido2 = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);


// Impresion
// scout << atoi(argv[3]) <<endl;
//  cout << k << " " << n << endl;
  ofstream fuerza_bruta("fuerza_bruta.dat", ios::app), dyv("dyv.dat", ios::app);
    if ( atoi(argv[3]) == 1 ){ // 3D
      fuerza_bruta << k << " " << n << " " <<  transcurrido2.count() << endl;
      dyv << k << " " << n << " " << transcurrido.count()<< endl;
    }
    else if ( atoi(argv[3]) == 2 ){ // kvectores, varian los vectores
      fuerza_bruta << k << " " << transcurrido2.count()<< endl;
      dyv << k << " " << transcurrido.count() << endl;
    }
    else if ( atoi(argv[3]) == 3 ){ //nelementos, varia el numero de elementos de cada vector
      fuerza_bruta << n << " " <<  transcurrido2.count() << endl;
      dyv << n << " " << transcurrido.count() << endl;
    }

  fuerza_bruta.close();
  dyv.close();
  delete [] aux;
}
