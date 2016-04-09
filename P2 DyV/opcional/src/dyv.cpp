#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>
#include <cstdlib>
#include <chrono>
using namespace std;



/* ************************************************************ */
/*  M�todo de ordenaci�n por mezcla  */

/**
   @brief Devuelve el numero de inversiones de un ranking.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   @return el numero de inversiones

   Calcula el numero de inversiones aplicando el algoritmo de mezcla.
   Como consecuencia tambien ordena el vector T.
*/
inline static
int inversiones(int T[], int num_elem);



/**
   @brief Devuelve el numero de inversiones de un ranking.

   @param T: vector de elementos. Tiene un n�mero de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar.
		   inicial < final.

  Calcula el numero de inversiones aplicando el algoritmo de mezcla.
  Como consecuencia tambien ordena el vector T.
*/
void inversiones_recursivo(int T[], int inicial, int final, int& num_inversiones);


/**
   @brief Ordena un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
inline static
void insercion(int T[], int num_elem);


/**
   @brief Ordena parte de un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar.
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la inserci�n.
*/
static void insercion_lims(int T[], int inicial, int final);


/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un n�mero de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a escribir.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a escribir
		   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El n�mero de elementos de U y V sumados debe coincidir
             con final - inicial.

   @return: El número de elementos que estaban desordenados

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
int fusion(int T[], int inicial, int final, int U[], int V[]);



/**
   Implementaci�n de las funciones
**/


int inversiones(int T[], int num_elem)
{
  int n = 0;
  inversiones_recursivo(T, 0, num_elem, n);
  return n;
}

void inversiones_recursivo(int T[], int inicial, int final, int& num_inversiones)
{
  if (final - inicial < 2)
    {
      return;
    } else {
      int k = (final - inicial)/2;

      int * U = new int [k - inicial];
      int l, l2;
      for (l = 0, l2 = inicial; l < k; l++, l2++)
	      U[l] = T[l2];

      int * V = new int [final - k];
      for (l = 0, l2 = k; l < final - k; l++, l2++)
	     V[l] = T[l2];

      inversiones_recursivo(U, 0, k, num_inversiones);
      inversiones_recursivo(V, 0, final - k, num_inversiones);
      num_inversiones += fusion(T, inicial, final, U, V);
      delete [] U;
      delete [] V;
    };
}


int fusion(int T[], int inicial, int final, int U[], int V[])
{
  int n_desordenados = 0;
  int k = (final-inicial)/2;
  for (int i =0; i < k-inicial; i++)
    for (int j=0; j < final-k; j++)
      if (U[i] > V[j])
        n_desordenados++;

  int i, j;
  for (i =0; i < k-inicial; i++)
    T[i] = U[i];
  for (i=0, j=k-inicial; j < final-k; i++, j++)
    T[j] = V[i];

  return n_desordenados;
}


int main(int argc, char** argv){
  if (argc < 2){
    cerr << "Formato " << argv[0] << " num_elem" << endl;
    return -1;
  }

  int n = atoi(argv[1]);
  int* rankings = new int[n];
  srandom(time(0));
  for (int i=0; i < n; i++){
    rankings[i] = i;
  }
  random_shuffle(rankings, rankings+n);

#ifndef GP_OUT
  cout << "ranking: ";
  for (int i=0; i<n; i++)
    cout << rankings[i] << " ";
  cout << endl;
#endif

  chrono::high_resolution_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;
  int n_inv;

  tantes = chrono::high_resolution_clock::now();
  n_inv = inversiones(rankings, n);
  tdespues = chrono::high_resolution_clock::now();
  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);

#ifndef GP_OUT
  cout << "Num inversiones: " << n_inv << endl;
#else
  cout << n << " " << transcurrido.count() << endl;
#endif
}
