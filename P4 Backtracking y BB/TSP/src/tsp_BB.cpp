#include "grafo.h"
#include <priority_queue>
struct Node{
  Path path;
  vector<Point> remaining;
  double pathLength;
  vector<double> = rowMinimums;
  Node(Path p, vector<Point> r, double pl, vector<double> rm){
    path = p;
    remaining = r;
    pathLength = pl;
    vector<double> = rm;
  }
  int numberOfBranches{
    remaining.size();
  }
  //Devuelve el i-ésimo nodo hijo.
  Node getSubnode(int i){
    Path subPath = Path(path);
    subPath.addPoint(remaining[i])
    vector<Point> subRemaining = remaining;
    subRemaining.remove(i);
    double subPathLength = pathLength + path.getLastPoint().distance(remaining[i]);
    vector<double> subRM = rowMinimums;
    subRM.remove(i);
    Node subnode = Node(subPath, subRemaining, subPathLength, subRM);
    return subnode;
  }
  double lowerBound(){
    double lb = pathLength;
    for (int i = 0; i < rowMinimums.size(); ++i)
      lb += rowMinimums[i];
    return lb;
  }
}
bool operator<(const Node& ln, const Node& rn){
  return ln.lowerBound() < rn.lowerBound();
}
Path Graph::TSP_BB(){
  DistanceMatrix dm = new DistanceMatrix(matrix, size);
  vector<double> rm = dm.rowMinimums();
  priority_queue<Node> queue;
  double optSolutionLength = 0;
  Path optPath;
  vector<Point> firstRemaining;
  Path firstP;
  for (int i = 0; i < size; ++i){
    firstRemaining.add(points[i]);
  }
  Node firstNode = Node(firstP, firstRemaining, 0, rm);
  queue.push(firstNode);
  while (!queue.empty()){
    if ((queue.top().lowerBound() > optSolutionLength) && (optSolutionLength != 0))
      queue.pop();
    else{
      if (queue.top().numberOfBranches == 0){
        double totalLength = queue.top().pathLength + queue.top().path.getLastPoint().distance(points[0]);
        if (totalLength < optSolutionLength){
          optSolutionLength = totalLength;
          optPath = queue.top().path;
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
