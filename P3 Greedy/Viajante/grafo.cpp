#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <vector>
#include <list>
using namespace std;

class Point{
   private:
      int x,y;
   public:
      Point(){
         x = y = -1;
      }
      Point(int abscisa, int ordenada){
         x = abscisa;
         y = ordenada;
      }
      Point(const Point &p){
         x = p.getX();
         y = p.getY();
      }

      int getX() const{
         return x;
      }
      int getY() const{
         return y;
      }

      void setX(const int &c){
         if ( c >= 0 )
            x = c;
      }
      void setY(const int &c){
         if ( c >= 0 )
            y = c;
      }
      void setXY(const int &c1, const int &c2){
         if ( c1 >= 0 && c2 >= 0 ){
            x = c1;
            y = c2;
         }
      }

      double Distance(const Point &p) const{
         return sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) );
      }

      Point& operator=(const Point &other){
         if (this != &other){
            x = other.getX();
            y = other.getY();
         }
         return *this;
      }
      bool operator==(const Point &other) const{
         return (x == other.getX() && y == other.getY());
      }
      bool operator!=(const Point &other) const{
         return (! (*this == other) );
      }
};

class Graph{
   private:
      int** matrix; // matrix nxn
      Point* points;
      int size;

      int* concretNearestNeighbour(int initial) const{
         int *neighbours = new int[size-1];
         int index_distance[2][size-1];
         int index, distance;

         for (int i=0; i<size; ++i){
            if (i < initial){
               index_distance[0][i] = i;
               index_distance[1][i] = matrix[i][initial];
               // Equivalente a matrix[initial][i], matrix simétrica
            }
            else if (i > initial){
               index_distance[0][i-1] = i;
               index_distance[1][i-1] = matrix[i][initial];
            }
         }

         for (int i=0; i<size; ++i){
            for (int j=i; j<size && (index_distance[1][j] < index_distance[1][j-1]) ; ++j){
               index = j-1;
               distance = index_distance[1][j-1];
               index_distance[0][j-1] = index_distance[0][j];
               index_distance[1][j-1] = index_distance[1][j];
               index_distance[0][j] = index;
               index_distance[1][j] = distance;
            }
         }

         for (int i=0; i<(size-1); ++i)
            neighbours[i] = index_distance[0][i];

         return neighbours;
      }

      int calcular_longitud(list<int> &lista){
        int ret = 0;
        list<int>::iterator next;

        for (auto it=lista.begin(); it!=lista.end(); ++it){
          next = it;
          ++next;
          if (next==lista.end()) next=lista.begin();

          ret += matrix[*it][*next];
        }

        return ret;
      }

      pair<int, list<int>::iterator> buscar_posicion(list<int> &lista, int nuevo){
        pair<int, list<int>::iterator> ret;
        int length;

        for (auto it = lista.begin(); it != lista.end(); ++it){
          if (it==lista.begin()){
            ret.second = it;
            lista.insert(it, nuevo);
            ret.first = calcular_longitud(lista);
            --it;
            lista.erase(it);
          }
          else{
            lista.insert(it, nuevo);
            length = calcular_longitud(lista);
            if (length < ret.first){
              ret.first = length;
              ret.second = it;
            }
            --it;
            lista.erase(it);
          }
        }

        return ret;
      }

      pair<int, list<int>::iterator> buscar_punto(list<int> &lista, bool* usados){
        pair<int, list<int>::iterator> ret, aux;
        bool can_compare = false;
        int minimo;

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

   class Edge{
      private:
         int first, second;
         double length;
      public:
         Edge(int a, int b, double ab):first(a), second(b), length(ab){}
         Edge():first(0), second(0), length(0){}

         void setEdge(int a, int b, double ab){
            first = a;
            second = b;
            length = ab;
         }

         int getFirst() const{
            return first;
         }

         int getSecond() const{
            return second;
         }

         int getLength() const{
            return length;
         }


         Edge& operator=(const Edge &other){
            if (this != &other){
               first = other.getFirst();
               second = other.getSecond();
               length = other.getLength();
            }
            return *this;
         }

         bool operator<(const Edge &other){
            return (length < other.getLength());
         }
         bool operator>=(const Edge &other){
            return ( !(length < other.getLength()) );
         }

   };

   public:
      Graph(Point* coordenadas, int n){
         if ( n > 0 ){
            points = new Point[n];
            for (int i=0; i<n; ++i)
               points[i] = coordenadas[i];

            matrix = new int*[n];
            for (int i=0; i<n; ++i){
               matrix[i] = new int[n];
               for (int j=i; j<n; ++j)
                  matrix[i][j] = matrix[j][i] = coordenadas[i].Distance(coordenadas[j]);
            }
            size = n;
         }
         else{
            size = 0;
            points = NULL;
            matrix = NULL;
         }
      }

      ~Graph(){
         if ( size > 0 ){
            for (int i=0; i<size; ++i)
               delete [] matrix[i];
            delete [] matrix;
         }
      }

      // Acceso a los datos miembro
      Point getPoint(const int &i) const{
         Point p;
         if ( i >= 0 )
            p = points[i];
         return p;
      }

      int getSize() const{
         return size;
      }

      // Funciones para los ciclos hamiltonianos

      int* nearestNeighbour(){
        int* order = new int[size];
        int* near;
        bool found = false, repeat;
        order[0] = 0;
        order[1] = concretNearestNeighbour(0)[0];

        for (int i=2; i<size; ++i){
            near = concretNearestNeighbour(i-1); // Devuelve un vector de size-1 elementos
            for (int j=0; j<(size-1) && !found; ++j){
                repeat = false;
                for (int k=0; k<i && !repeat; ++k){
                    if (near[j] == order[i])
                        repeat = true;
                }

                if (!repeat){
                    order[i] = near[j];
                    found = true;
                }
            }
        }

        return order;
      }


      int* minimizingEdges(){
          vector< vector<Edge> > paths;
          vector<Edge> orderedEdges, aux;
          vector<Edge>::iterator it;
          Edge item, temp;
          int i, j, k;

          for (i=0; i<size; ++i){
             for (j=0; j<size; ++j){
                item.setEdge(i, j, matrix[i][j]);
                orderedEdges.push_back(item); // size*size elementos
             }
          }

          // Heapsort
          for(k=size*size; k>0; --k){
             for(i=1; i<=k; ++i){
                item = orderedEdges[i];
                j = i/2;
                while(j>0 && orderedEdges[j]<item){
                    orderedEdges[i] = orderedEdges[j];
                    i = j;
                    j = j/2;
                }
                orderedEdges[i] = item;
             }
             temp = orderedEdges[1];
             orderedEdges[1] = orderedEdges[k];
             orderedEdges[k] = temp;
          }
          // Comprobar que ordena


          int length = 0, end = size*size;
          bool finish = false, first, second, insert;


          paths.push_back(aux);
          paths[0].push_back(orderedEdges[0]);


         /* Caso 1(bien): Ninguno está       #-----------#  *--*

            Caso 2(mal): Están los dos       +------*
                    Ciclo                    |      |
                                             +------*

            Caso 3(bien): Está uno           #-----------*--*

            Caso 4(mal): Está uno en mitad   #------*----#
                                                    |
                                                    *

            Caso 5(mal): Están los dos       #---*--*----# IMPOSIBLE
         */
          for (i=1; i<end && !finish; ++i){
             first = second = insert = false; // Comprobamos si los vertices ya están en los caminos

             for (j=0; j<abs(paths.size()) && !insert; ++j){ //Comprobamos que no forma ciclo con cada camino formado

                for (k=0; k<abs(paths[j].size()); ++k){
                    if ( paths[j][k].getFirst() == orderedEdges[i].getFirst() ||
                         paths[j][k].getSecond() == orderedEdges[i].getFirst() )
                        first = true;
                    if ( paths[j][k].getFirst() == orderedEdges[i].getSecond() ||
                         paths[j][k].getSecond() == orderedEdges[i].getSecond() )
                        second = true;
                }
                // Caso 2 (first && second)

                if ( !first && !second ){ // Caso 1
                    vector<Edge> newPath;
                    newPath.push_back(orderedEdges[i]);
                    paths.push_back(newPath);
                    insert = true;
                }
                // Permutamos para que nos salgan las aristas en orden
                else if ( first && !second ){
                    if ( paths[j][0].getFirst()  == orderedEdges[i].getFirst() ){
                        paths[j].insert(paths[j].begin(),
                                 Edge(orderedEdges[i].getSecond(), orderedEdges[i].getFirst(), orderedEdges[i].getLength()) );
                        insert = true;
                    }
                    else if ( paths[j][0].getSecond() == orderedEdges[i].getFirst() ){
                        paths[j][0].setEdge(paths[j][0].getSecond(), paths[j][0].getFirst(), paths[j][0].getLength());
                        paths[j].insert(paths[j].begin(),
                                 Edge(orderedEdges[i].getSecond(), orderedEdges[i].getFirst(), orderedEdges[i].getLength()) );
                        insert = true;
                    }

                }
                else if ( !first && second){
                    if ( paths[j][0].getFirst()  == orderedEdges[i].getSecond() ){
                        paths[j].insert(paths[j].begin(), orderedEdges[i] );
                        insert = true;
                    }
                    else if ( paths[j][0].getSecond() == orderedEdges[i].getSecond() ){
                        // Permutamos para que nos salga en orden
                        paths[j][0].setEdge(paths[j][0].getSecond(), paths[j][0].getFirst(), paths[j][0].getLength());
                        paths[j].insert(paths[j].begin(), orderedEdges[i] );
                        insert = true;
                    }
                }

             }

             if (length == size)// Habrá size aristas
                finish = true;
          }

          int* ret = new int[size]; // Índices ordenados
          int duration = paths[0].size();
          bool index[paths.size()]; // Almacena si hemos metido ya el camino i-esimo en ret
          for (i=0; i<abs(paths.size()); ++i)
            index[i] = false;
          index[0] = true;

          for (i=0; i<duration; ++i)
            ret[i] = paths[0][i].getSecond();

          while (duration < size){
              for (i=0; i<abs(paths.size()); ++i){
                 if (index[i] == false){ // Aún no se ha incluido paths[i]
                    if (paths[i][0].getFirst() == ret[duration-1]){
                        for (j=0; j<abs(paths[i].size()); ++j){
                            ret[duration] = paths[i][j].getSecond();
                            ++duration;
                        }
                        index[i] = true;
                    }
                    else if (paths[i][ paths[i].size()-1 ].getSecond() == ret[duration-1]){
                        for (j=paths[i].size()-1; j>=0; --j){
                            ret[duration] = paths[i][j].getFirst();
                            ++duration;
                        }
                        index[i] = true;
                    }
                 }
              }
          }
          return ret;
      }

      int* insertion(){
        int* permutation = new int[size];
        list<int> recorrido;      // Lista que controla el recorrido parcial
        bool* usados = new bool[size];    // Vector de bits que controla los puntos que ya he usado.
        int este = 0, oeste, norte;   // Inicializamos el este al índice 0

        // Inicializamos el vector de booleanos
        for (int i=0; i<size; ++i)
          usados[i] = false;

        // Buscamos el que está más al este
        for (int i=1; i<size; ++i)
          if (points[este].getX()<points[i].getX()) este = i;
        usados[este] = true;
        recorrido.push_back(este);

        oeste = (este==0)?1:0;    // Inicializamos el oeste al menor índice posible

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

        return permutation;
      }
};

Point * readPoints(std::ifstream &in, int &size){
  char aux;
  int dim, x, y;
  Point* points = NULL;
  while( in.peek() < '0' || in.peek() > '9' ) // Buscar dimensión
    in >> aux;
  in >> dim;

  if (dim > 0){
      size = dim;
      points = new Point[size];
      for (int i=0; i<size; ++i){
        in >> dim >> x >> y;
        points[i].setXY(x, y);
      }
  }

  return points;
}

int main(int argc, char* argv[]){
  bool exit = false;
  if (argc != 4){
    cerr << "Formato: " << argv[0] << " <fichero.dat>" << " <modo>" << " <num_ciudades>" << endl;
    cerr << "Modo:\n\t1 --> Vecino más cercano\n\t 2 --> Inserción\n\t3 --> Minimizando aristas" << endl;
    return -1;
  }

  ifstream in(argv[1]);
  int mode = atoi(argv[2]);
  int cities = atoi(argv[3]);
  if (!in){
    cerr << "No se puede abri el fichero " << argv[1] << " para lectura." << endl;
    exit = true;
  }
  if ( mode > 3 || mode < 1 ){
    cerr << "Modo incorrecto" << endl;
    cerr << "Modo:\n\t1 --> Vecino más cercano\n\t 2 --> Inserción\n\t3 --> Minimizando aristas" << endl;
    exit = true;
  }
  if (cities < 3 || cities > 300){
    cerr << "El número de ciudades debe estar entre 3 y 300 inclusive." << endl;
    exit = true;
  }

  if (exit)
    return -1;

  srandom(time(0));
  int size;
  int* order;
  Point* points = readPoints(in, size);
  Graph graph(points, size);

  chrono::high_resolution_clock::time_point tbefore, tafter;
  chrono::duration<double> duration;

  tbefore = chrono::high_resolution_clock::now();
  if (mode == 1)
    order = graph.nearestNeighbour();
  else if (mode == 2)
    order = NULL;
    //order = graph.insertion_____();
  else // mode == 3
    order = graph.minimizingEdges();
  tafter = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::duration<double>>(tafter - tbefore);

  ofstream solution("order.dat");
  for (int i=0; i<size; ++i)
    solution << order[i] << graph.getPoint(order[i]).getX() << graph.getPoint(order[i]).getY() << endl;


}
