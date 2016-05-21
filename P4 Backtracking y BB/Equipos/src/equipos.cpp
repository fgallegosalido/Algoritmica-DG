#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;


// Algoritmo equivalente a sumar 1 a un número en binario
void siguiente(vector<bool>& comb){
   bool extra = true;
   for (int i=(comb.size()-1); i>= 0; --i){
      if (extra){
         if (comb[i] == false){
            comb[i] = true;
            extra = false;
         }
         else
            comb[i] = false;
      }
   }
}

void siguienteEquilibrado(vector<bool>& comb, unsigned int& t/*trues*/, unsigned int& f/*falses*/, bool& par){
   bool extra = true;
   for (int i=(comb.size()-1); i>= 0; --i){
      if (extra){
         if (comb[i] == false){
            comb[i] = true;
            extra = false;
            --f;
            ++t;
         }
         else{
            comb[i] = false;
            ++f;
            --t;
         }
      }
   }
   if (par){
      if (t != f)
         siguienteEquilibrado(comb, t, f, par);
   }
   else if ( abs(t-f) > 1){
      siguienteEquilibrado(comb, t, f, par);
   }
}

// Función que divide en dos equipos, minimizando la diferencia de niveles.
// Parámetros: vector de enteros, los niveles de cada persona.
// Devuelve: vector de bool que indica los equipos
vector<unsigned int> DivideEnDosEquipos(vector<unsigned int> players, unsigned int& dist, bool equillibrados=false){
   vector<unsigned int> ret;
   vector<bool> teams, bestTeam;
   bool ultimaEjecucion = false, par;
   unsigned int puntuacion1, puntuacion2; // Valor de cada equipo
   unsigned int distancia = 0; // Futura cota cota global del backtracking
   unsigned int t, f; // Usados solamente si queremos equipos equillibrados
   unsigned int tam = players.size();
   unsigned int i, localT, localF;

   par = ( tam%2 == 0 );
   t = 0;
   f = players.size();

   teams.reserve(tam);
   bestTeam.reserve(tam);
   for (i=0; i<tam; ++i){
      distancia += players[i];
      teams.push_back(false);
      bestTeam.push_back(false);
   }

   // Backtracking, "distancia" ahora mismo es cota superior
   while(ultimaEjecucion == false){
      ultimaEjecucion = true;
      // Comprobamos que no es la última iteración
      if (equillibrados == false){
         for (i=0; i<tam && ultimaEjecucion; ++i){
            if (teams[i] == false)
               ultimaEjecucion = false;
         }
      }
      else{
         if (par){
            for (i=0; i<tam/2 && ultimaEjecucion; ++i){
               if (teams[i] == false)
                  ultimaEjecucion = false;
            }
            for (i=tam/2; i<tam && ultimaEjecucion; ++i){
               if (teams[i] == true)
                  ultimaEjecucion = false;
            }
         }
         else{
            for (i=0; i<(tam/2+1) && ultimaEjecucion; ++i){
               if (teams[i] == false)
                  ultimaEjecucion = false;
            }
            for (i=(tam/2+1); i<tam && ultimaEjecucion; ++i){
               if (teams[i] == true)
                  ultimaEjecucion = false;
            }
         }
      }
      // ------------------------------------------------------

      if (!ultimaEjecucion){
         puntuacion1 = puntuacion2 = 0;
         if (equillibrados == false)
            siguiente(teams);
         else
            siguienteEquilibrado(teams, t, f, par);

         for (int i=0; i<teams.size(); ++i){
            if( teams[i] )
               puntuacion1 += players[i];
            else
               puntuacion2 += players[i];
         }

         if (abs(puntuacion1-puntuacion2) < distancia){
            distancia = abs(puntuacion1-puntuacion2);
            bestTeam = teams;
            localT = t;
            localF = f;
         }
      }
   }

   for (int i=0; i<tam; ++i){
      if (bestTeam[i])
         ret.push_back( players[i] );
   }

   dist = distancia;
   return ret;
}




int main(int argc, char* argv[]){
   if (argc != 3){
      std::cerr << "Sintáxis: " << argv[0] << " <número_personas> <1/0(equipos equillibrados)>" <<std::endl;
      return -1;
   }

   bool equillibrados = atoi(argv[2]);
   unsigned int n = atoi(argv[1]), distance;
   vector<unsigned int> players, teams;

   srand(time(0));

   for (int i=0; i<n; ++i)
      players.push_back( (int) (rand()%1000 +1) );


   std::chrono::high_resolution_clock::time_point tantes, tdespues;
   std::chrono::duration<double> transcurrido, transcurrido2;
   tantes = std::chrono::high_resolution_clock::now();

   teams = DivideEnDosEquipos(players, distance, equillibrados);

   tdespues = std::chrono::high_resolution_clock::now();
   transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(tdespues - tantes);



   std::cout << n << " " << transcurrido.count() << std::endl;
   ofstream os("distancia.txt");
   os << distance;
   os.close();

   unsigned int sep = abs( players.size() - 2*teams.size() );
   ofstream os2("separacion.txt");
   os2 << players.size() <<"-"<<teams.size(); 
   os2.close();
}
