#include <queue>
#include <vector>
#include <functional>
#include "grafo.h"
using namespace std;

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
           matrix[i][j] = matrix[j][i] = coordenadas[i].distance(coordenadas[j]);
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


// Estructura que guarda un camino y la cota de su coste
struct PathAndCost{
  Path path;
  double cost;
  vector<Point> leftPoints; // Puntos que quedan para cerrar el ciclo
  vector<int> indexes; // Índices en "points[]" de los puntos que tiene el camino
  bool operator< (const PathAndCost& rhs) const {
    return cost < rhs.cost;
  }
  bool operator> (const PathAndCost& rhs) const {
    return cost > rhs.cost;
  }
};


// Suma los valores de rm excluyendo los indices de p
int sum(vector<double> rm, PathAndCost &p){
  int count = 0;
  int j = 0;
  for (int i=0; i < rm.size(); ++i){
    if (i != p.indexes[j])
      count += rm[i];
    else
      j = j < p.indexes.size() - 1 ? j + 1 : j;
  }

  return count;
}


Path Graph::TSP_BB(int& nodes, int& queueMaxSize, int& cuts, int typeEstimate){
   DistanceMatrix dm(matrix, size);
   vector<double> rm = dm.rowMinimums();
   priority_queue<PathAndCost, vector<PathAndCost>, greater<PathAndCost> > liveNodesQueue;
   double optSolutionLength = 0;
   Path optPath;

   nodes = queueMaxSize = cuts = 0;

   // Genera las permutaciones del primer nivel
   PathAndCost p;
   for (int i = 1; i < size; ++i){
     p.path.addPoint(points[0]);
     p.path.addPoint(points[i]);
     p.leftPoints = vector<Point>(points, points + size); // conversion a std::vector de points[]
     p.leftPoints.erase(p.leftPoints.begin());
     p.leftPoints.erase(p.leftPoints.begin()+i);
     p.indexes.push_back(0);
     p.indexes.push_back(i);
     p.cost = sum(rm, p) + p.path.getLength();
     liveNodesQueue.push(p); // ¡Bad Alloc!
   }

   // FIX Este bucle no acaba aún poniendo solo 4 puntos
   while (!liveNodesQueue.empty()){
      if (queueMaxSize < liveNodesQueue.size())
         queueMaxSize = liveNodesQueue.size(); //

      PathAndCost p = liveNodesQueue.top();
      for (int i=0; i < p.leftPoints.size(); ++i){
        p.path.addPoint(p.leftPoints[i]);
        p.leftPoints.erase(p.leftPoints.begin()+i);
        p.indexes.push_back(i);
        p.cost = sum(rm, p) + p.path.getLength();
        if (p.path.getNumPoints() == size-2 && p.cost < optSolutionLength && optSolutionLength != 0){
          p.path.addPoint(p.leftPoints[0]);
          p.path.addPoint(points[0]);
          optSolutionLength = p.path.getLength();
          optPath = p.path;
        }
        liveNodesQueue.push(p);
      }

      while ((liveNodesQueue.top().cost >= optSolutionLength) && (optSolutionLength != 0)){
         liveNodesQueue.pop();
         ++cuts; //
      }
   }

   return optPath;
}
