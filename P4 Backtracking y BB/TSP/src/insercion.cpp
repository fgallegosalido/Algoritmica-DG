#include "grafo.h"

// Calcula la longitud del recorrido definido por la lista
double Graph::calcular_longitud(list<int> &lista){
   double ret = 0;
   list<int>::iterator next;

   for (auto it=lista.begin(); it!=lista.end(); ++it){
      next = it;
      ++next;
      if (next==lista.end()) next=lista.begin();

      ret += matrix[*it][*next];
   }

   return ret;
}

// Función que para un punto dado busca la posición que minimiza el recorrido,
// y devuelve la longitud mínima para dicho punto y el iterador que la genera
pair<double, list<int>::iterator> Graph::buscar_posicion(list<int> &lista, int nuevo){
   pair<double, list<int>::iterator> ret;
   list<int>::iterator aux, aux2;
   double length;
   double original_length = calcular_longitud(lista);

   for (auto it = lista.begin(); it != lista.end(); ++it){
      if (it==lista.begin()){
         aux = lista.end();
         --aux;
         ret.first = original_length - matrix[*aux][*it];
         lista.insert(it, nuevo);
         ret.first = ret.first + matrix[*(lista.begin())][*it] + matrix[*aux][*(lista.begin())];
         it = ret.second = lista.erase(it);
      }
      else{
         aux = it;
         --aux;
         length = original_length - matrix[*it][*aux];
         lista.insert(it, nuevo);
         aux2 = it;
         --aux2;
         length = length + matrix[*aux][*aux2] + matrix[*aux2][*it];
         if (length < ret.first){
            ret.first = length;
            ret.second = it;
         }
         lista.erase(aux2);
      }
   }

   return ret;
}

pair<int, list<int>::iterator> Graph::buscar_punto(list<int> &lista, bool* usados){
   pair<int, list<int>::iterator> ret;
   pair<double, list<int>::iterator> aux;
   bool can_compare = false;
   double minimo;

   // Vamos comprobando cada punto y nos quedamos al final con el mejor
   for (int i=0; i<size; ++i){
      if (!usados[i]){
         if (!can_compare){
            can_compare = true;
            aux = buscar_posicion(lista, i);

            ret.first = i;
            ret.second = aux.second;
            minimo = aux.first;
         }
         else{
            aux = buscar_posicion(lista, i);
            if (aux.first < minimo){
               ret.first = i;
               ret.second = aux.second;
               minimo = aux.first;
            }
         }
      }
   }
   return ret;
}

// Algoritmo de inserción para el problema del viajante
int* Graph::insertion(double &tam){
   int* permutation = new int[size];
   list<int> recorrido;         // Lista que controla el recorrido parcial
   bool* usados = new bool[size];      // Vector de bits que controla los puntos que ya he usado.
   int este = 0, oeste, norte;    // Inicializamos el este al índice 0

   // Inicializamos el vector de booleanos
   for (int i=0; i<size; ++i)
      usados[i] = false;

   // Buscamos el que está más al este
   for (int i=1; i<size; ++i)
      if (points[este].getX()<points[i].getX()) este = i;
   usados[este] = true;
   recorrido.push_back(este);

   oeste = (este==0)?1:0;      // Inicializamos el oeste al menor índice posible

   // Buscamos el que está más al oeste
   for (int i=0; i<size; ++i)
      if (points[oeste].getX()>points[i].getX() && i!=este) oeste = i;
   usados[oeste] = true;
   recorrido.push_back(oeste);

   // Inicializamos el norte al menor índice posible
   if (este>0 && oeste>0) norte = 0;
   else if ((este==0 && oeste>1) || (oeste==0 && este>1)) norte = 1;
   else norte = 2;

   // Buscamos el que está más al norte
   for (int i=0; i<size; ++i)
      if (points[norte].getY()<points[i].getY() && i!=este && i!=oeste) norte = i;
   usados[norte] = true;
   recorrido.push_back(norte);

   pair<int, list<int>::iterator> insertor;

   // Vamos creando la lista del recorrido
   while (recorrido.size() < size){
      insertor = buscar_punto(recorrido, usados);
      recorrido.insert(insertor.second, insertor.first);
      usados[insertor.first] = true;
   }

   for (int i=0; i<size; ++i){
      permutation[i] = recorrido.front();
      recorrido.pop_front();
   }

   list<int> l;
   for(int i=0; i<size; ++i)
      l.push_back(permutation[i]);
   tam = calcular_longitud(l);

   return permutation;
}
