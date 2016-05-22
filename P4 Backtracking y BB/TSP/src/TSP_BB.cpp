#include <vector>
#include <queue>
#include "grafo.h"

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
