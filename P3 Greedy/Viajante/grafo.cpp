#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <ctime>

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

      Point& operator=(const Point &otro){
         if (this != &otro){
            x = otro.getX();
            y = otro.getY();
         }
         return *this;
      }
      bool operator==(const Point &otro) const{
         return (x == otro.getX() && y == otro.getY());
      }
      bool operator!=(const Point &otro) const{
         return (! (*this == otro) );
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
        order[1] = concretNearestNeighbour(0);
        
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
          return NULL;
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
  int size, node;
  int* order;
  Point* points = readPoints(in, size);
  Graph graph(points, size);
  node = 0;

  chrono::high_resolution_clock::time_point tbefore, tafter;
  chrono::duration<double> duration;
  
  tbefore = chrono::high_resolution_clock::now();
  if (mode == 1)
    order = graph.nearestNeighbour(node);
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
  

  
