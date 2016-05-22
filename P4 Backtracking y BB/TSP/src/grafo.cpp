#include "grafo.h"
#include "node.h"
#include "BBtools.h"
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




Path Graph::TSP_BB(){
   DistanceMatrix dm(matrix, size);
   vector<double> rm = dm.rowMinimums();
   priority_queue<Node> queue;
   double optSolutionLength = 0;
   Path optPath;
   vector<Point> firstRemaining;
   Path firstP;

   for (int i = 0; i < size; ++i)
      firstRemaining.push_back(points[i]);

   Node firstNode = Node(firstP, firstRemaining, 0, rm);
   queue.push(firstNode);

   while (!queue.empty()){
      if ((queue.top().lowerBound() > optSolutionLength) && (optSolutionLength != 0))
         queue.pop();
      else{
         if (queue.top().numberOfBranches() == 0){
            double totalLength = queue.top().getPathLength() + queue.top().getPath().getLastPoint().distance(points[0]);
            if (totalLength < optSolutionLength){
               optSolutionLength = totalLength;
               optPath = queue.top().getPath();
            }
            queue.pop();
         }
         else{
            for (int i = 0; i < queue.top().numberOfBranches(); ++i)
               queue.push(queue.top().getSubnode(i));
         }
      }
   }

   return optPath;
}
