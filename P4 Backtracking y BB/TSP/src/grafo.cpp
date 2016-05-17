#include "grafo.h"

// Constructor
Graph::Graph(Point* coordenadas, int n){
  if ( n > 0 ){
    points = new Point[n];
    for (int i=0; i<n; ++i)
      points[i] = coordenadas[i];

    matrix = new double*[n];

    for (int i=0; i<n; ++i)
      matrix[i] = new double[n];
    for (int i=0; i<n; ++i){
      for (int j=i; j<n; ++j)
        matrix[i][j] = matrix[j][i] = coordenadas[i].Distance(coordenadas[j]);
    }
    size = n;
  }
  else{
    size = 0;
    points = 0;
    matrix = 0;
  }
}

// Destructor
Graph::~Graph(){
  if ( size > 0 ){
    for (int i=0; i<size; ++i)
      delete [] matrix[i];
    delete [] matrix;
  }
}

// Acceso a los datos miembro
Point Graph::getPoint(const int &i) const{
  Point p;
  if ( i >= 0 )
    p = points[i];

  return p;
}
