#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

// Función que divide en dos equipos, haciendo que la suma de los niveles sea
// lo más parecida posible.
// Se le pasan como parámetros un vector de enteros que se corresponden con el
// nivel de cada persona; y el tamaño del vector.
// Devuelve un vector de enteros de tamaño n/2, correspondiente a uno de los
// dos equipos (el otro se puede sacar a partir de este).
int* DivideEnDosEquipos(int* array, int size){
  int *ret = new int[size/2];
  return ret;
}

int main(int argc, char* argv[]){
  if (argc != 2){
    std::cerr << "Sintáxis: " << argv[0] << " <número_personas>" << std::endl;
    return -1;
  }

  int n = atoi(argv[1]);
  int *aux = new int[n];
  int *team;

  srand(time(0));

  for (int i=0; i<n; ++i)
    aux[i] = rand()%n;

  std::chrono::high_resolution_clock::time_point tantes, tdespues;
  std::chrono::duration<double> transcurrido, transcurrido2;
  tantes = std::chrono::high_resolution_clock::now();

  team = DivideEnDosEquipos(aux, n);

  tdespues = std::chrono::high_resolution_clock::now();
  transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(tdespues - tantes);

  std::cout << n << " " << transcurrido.count() << std::endl;

  delete[] aux;
}
