#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <vector>
using namespace std;


// Algoritmo equivalente a sumar 1 a un número en binario
void siguiente(vector<bool>& comb){
   bool acarreo = true;
   for (int i=(comb.size()-1); i>= 0; --i){
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
vector<unsigned int> DivideEnDosEquipos(vector<unsigned int> players){
   vector<unsigned int> ret;
   vector<bool> teams, bestTeam;
   bool ultimaEjecucion = false;
   unsigned int puntuacion1, puntuacion2; // Valor de cada equipo
   unsigned int distance = 0; // Futura cota cota global del backtracking

   for (int i=0; i<players.size(); ++i){
      distance += players[i];
      teams.push_back(false);
      bestTeam.push_back(false);
   }

   // Backtracking, "distance" ahora mismo es cota superior
   while(ultimaEjecucion == false){

      for(int i=0;i<teams.size(); ++i)
         cout << teams[i] ;
      cout << endl;

      ultimaEjecucion = true;
      // Comprobamos que no es la última iteración
      for (int i=0; i<teams.size() && ultimaEjecucion; ++i){
         if (teams[i] == false)
            ultimaEjecucion = false;
      }

      if (!ultimaEjecucion){
         puntuacion1 = puntuacion2 = 0;
         siguiente(teams);

         for (int i=0; i<teams.size(); ++i){
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

   for (int i=0; i<bestTeam.size(); ++i){
      if (bestTeam[i])
         ret.push_back( players[i] );
   }

   return ret;
}

int main(int argc, char* argv[]){
   if (argc != 2){
      std::cerr << "Sintáxis: " << argv[0] << " <número_personas>" << std::endl;
      return -1;
   }

   int n = atoi(argv[1]);
   vector<unsigned int> players, teams;

   srand(time(0));

   for (int i=0; i<n; ++i)
      players.push_back( (int) (rand()%100 +1) );


   std::chrono::high_resolution_clock::time_point tantes, tdespues;
   std::chrono::duration<double> transcurrido, transcurrido2;
   tantes = std::chrono::high_resolution_clock::now();

   teams = DivideEnDosEquipos(players);

   tdespues = std::chrono::high_resolution_clock::now();
   transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(tdespues - tantes);

   std::cout << n << " " << transcurrido.count() << std::endl;
}
