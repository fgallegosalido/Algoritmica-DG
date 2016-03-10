/**
   @file C�lculo de la sucesi�n de Fibonacci
*/


#include <iostream>
using namespace std;
#include <ctime>
#include <chrono>


/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char **argv)
{
  if (argc != 2)
  {
    cerr << "Formato " << argv[0] << " <valor_fib>" << endl;
    return -1;
  }

  int n = atoi(argv[1]);
  int f;
  chrono::high_resolution_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  tantes = chrono::high_resolution_clock::now();
  f = fibo(n);
  tdespues = chrono::high_resolution_clock::now();
  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);

  /// Formato de salida para GNUPlot, x elemento, y tiempo
  cout << n << " " << transcurrido.count() << endl;

  return 0;
}
