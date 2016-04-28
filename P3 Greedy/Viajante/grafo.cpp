#include <iostream>
#include <fstream>
#include <cmath>

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

      // Funciones para los ciclos hamiltonianos
      int* nearestNeighbour(int &initial) const{
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
};

int main(){
   int x = 5;
}
