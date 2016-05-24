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





Path Graph::TSP_BB(int& nodes, int& queueMaxSize, int& cuts, int typeEstimate){
   DistanceMatrix dm(matrix, size);
   vector<double> rm = dm.rowMinimums();
   priority_queue<Node> queue;
   double optSolutionLength = 0;
   Path optPath, firstP;
   vector<Point> firstRemaining;
   
   nodes = queueMaxSize = cuts = 0;


   for (int i = 0; i < size; ++i)
      firstRemaining.push_back(points[i]);

   Node firstNode = Node(firstP, firstRemaining, 0, rm);
   queue.push(firstNode);

   while (!queue.empty()){
      if (queueMaxSize < queue.size())
         queueMaxSize = queue.size(); //

      if ((queue.top().lowerBound() > optSolutionLength) && (optSolutionLength != 0)){
         queue.pop();
         ++cuts; // 
      }
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
            for (int i = 0; i < queue.top().numberOfBranches(); ++i){
               queue.push(queue.top().getSubnode(i));
               ++nodes; // 
            }
         }
      }
   }

   return optPath;
}

