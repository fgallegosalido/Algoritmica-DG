/**
   @file C�lculo de la sucesi�n de Fibonacci
*/


#include <iostream>
using namespace std;
#include <ctime>


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

  f = fibo(n);

  cout << "El t�rmino " << n << "-�simo es: " << f << endl;

  return 0;
}
