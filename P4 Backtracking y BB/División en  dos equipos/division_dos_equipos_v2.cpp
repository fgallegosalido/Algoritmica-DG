// Versión que usa int* y no vector<int>. Algo más rápida
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

// Algoritmo equivalente a sumar 1 a un número en binario
void siguiente(bool* comb, int size){
   bool acarreo = true;
   for (int i=(size-1); i>= 0; --i){
      if (acarreo){
         if (comb[i] == false){
            comb[i] = true;
            acarreo = false;
         }
         else
            comb[i] = false;
      }
   }
}

// Función que divide en dos equipos, minimizando la diferencia de niveles.
// Parámetros: vector de enteros, los niveles de cada persona.
// Devuelve: vector de bool que indica los equipos
int* DivideEnDosEquipos(int* players, int size){
   int* ret;
   bool* teams = new bool[size];
   bool* bestTeam = new bool[size];
   bool ultimaEjecucion = false;
   int puntuacion1, puntuacion2; // Valor de cada equipo
   int distance = 0; // Futura cota cota global del backtracking

   for (int i=0; i<size; ++i){
      distance += players[i];
      teams[i] = false;
      bestTeam[i] = false;
   }

   // Backtracking, "distance" ahora mismo es cota superior
   while(ultimaEjecucion == false){

      ultimaEjecucion = true;
      // Comprobamos que no es la última iteración
      for (int i=0; i<size && ultimaEjecucion; ++i){
         if (teams[i] == false)
            ultimaEjecucion = false;
      }

      if (!ultimaEjecucion){
         puntuacion1 = puntuacion2 = 0;
         siguiente(teams, size);

         for (int i=0; i<size; ++i){
            if( teams[i] )
               puntuacion1 += players[i];
            else
               puntuacion2 += players[i];
         }

         if (abs(puntuacion1-puntuacion2) < distance){
            distance = abs(puntuacion1-puntuacion2);
            bestTeam = teams;
         }
      }
   }

   int count = 0;
   for (int i=0; i<size; ++i){
      if (bestTeam[i]) count++;
   }

   ret = new int[count];

   for (int i=0; i<size; ++i){
      if (bestTeam[i])
         ret[i] = players[i];
   }

   return ret;
}

int main(int argc, char* argv[]){
   if (argc != 2){
      std::cerr << "Sintáxis: " << argv[0] << " <número_personas>" << std::endl;
      return -1;
   }

   int n = atoi(argv[1]);
   int* teams;
   int* players = new int[n];

   srand(time(0));

   for (int i=0; i<n; ++i)
      players[i] = rand()%100 +1;



   std::chrono::high_resolution_clock::time_point tantes, tdespues;
   std::chrono::duration<double> transcurrido, transcurrido2;
   tantes = std::chrono::high_resolution_clock::now();

   teams = DivideEnDosEquipos(players, n);

   tdespues = std::chrono::high_resolution_clock::now();
   transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(tdespues - tantes);

   std::cout << n << " " << transcurrido.count() << std::endl;
}
