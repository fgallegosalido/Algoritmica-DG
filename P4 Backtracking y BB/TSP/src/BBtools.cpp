#include <vector>
#include "BBtools.h"
#include "point.h"
using namespace std;

Path::Path(){
    path.clear();
}

Path::Path(const Path& p){
   path = p.getPath();
}

Path Path::getPath() const{
   return path;
}

double Path::getLength() const{
   double length = 0;
   for (int i = 1; i < path.size; ++i)
      length += path[i-1].distance(path[i]);
   return length;
}

void Path::addPoint(const Point& p){
   path.add(p);
}

Point Path::getLastPoint() const{
   path[path.size-1];
}



// DistanceMatrix classs
DistanceMatrix::DistanceMatrix(const int& n){
   D = new double*[n];
   for (int i=0; i<n; ++i)
      D[i] = new double[n];
   dimension = n;
}

DistanceMatrix::DistanceMatrix(double** m, const int& n){
   D = new double*[n];
   for (int i=0; i<n; ++i)
      D[i] = new double[n];
   for (int i=0; i<n; ++i){
      for (int j=i; j<n; ++j){
         D[i][j] = m[i][j];
         D[j][i] = m[i][j];
      }
   }
   dimension = n;
}

DistanceMatrix DistanceMatrix::Submatrix(const int& m, const int& n){
   DistanceMatrix newD = DistanceMatrix(dimension-1);
   for (int i = 0; i < dimension; ++i){
      for (int j = 0; j < dimension; ++j){
         if (i < m)
            if (j < n)
               newD[i][j] = D[i][j];
            else
               newD[i][j] = D[i][j+1];
         else
            if (j < n)
               newD[i][j] = D[i+1][j];
            else
               newD[i][j] = D[i+1][j+1];
      }
   }
   return newD;
}

vector<double> DistanceMatrix::rowMinimums() const{
   vector<double> row_min;
   row_min.add(D[0][1]);
   for (int j = 2; j < dimension; ++j){
      if (D[0][j] < row_min[0])
         row_min[0] = D[0][j];
   }
   for (int i = 1; i < dimension; ++i){
      row_min.add(D[i][0]);
      for (int j = 1; j < i; ++j)
         if (D[i][j] < row_min[i])
            row_min[i] = D[i][j];
      for (int j = i+1; j < dimension; ++j)
         if (D[i][j] < row_min[i])
            row_min[i] = D[i][j];
   }
   return row_min;
}

   // Cota inferior parcial por defecto (mínimo de cada fila)
double DistanceMatrix::PartialBound() const{
   int row_min[dimension];
   double sum = 0;
   row_min[0] = D[0][1];
   for (int j = 2; j < dimension; ++j){
      if (D[0][j] < row_min[0])
         row_min[0] = D[0][j];
   }
   for (int i = 1; i < dimension; ++i){
      row_min[i] = D[j][0];
      for (int j = 1; j < i; ++j)
         if (D[i][j] < row_min[i])
            row_min[i] = D[0][j];
      for (int j = i+1; j < dimension; ++j)
         if (D[i][j] < row_min[i])
            row_min[i] = D[i][j];
   }
   for (int i = 0; i < dimension; ++i)
      sum += row_min[i];
   return sum;
}

//Cota propuesta por Francisco
double DistanceMatrix::PartialBound2(){
   // IMPLEMENTACIÓN
   return 0;
}

   //Cota propuesta por Rubén
double DistanceMatrix::PartialBound3(){
   // IMPLEMENTACIÓN
   return 0;
}
