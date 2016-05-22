#include <queue>
#include <vector>
#include "point.h"
#include "BBtools.h"

#include "node.h"
using namespace std;

Node::Node(const Path& p, vector<Point> r, const double& pl, vector<double> rm):path(p){
   remaining = r;
   pathLength = pl;
   rowMinimums = rm;
}

int Node::numberOfBranches() const{
   return remaining.size();
}

//Devuelve el i-ésimo nodo hijo.
Node Node::getSubnode(int& i) const{
   Path subPath = Path(path);
   subPath.addPoint(remaining[i]);

   vector<Point> subRemaining = remaining;
   subRemaining.erase(subRemaining.begin() + i); //--

   double subPathLength = pathLength + path.getLastPoint().distance(remaining[i]);
   vector<double> subRM = rowMinimums;
   subRM.erase(subRM.begin() + i); // ----
   Node subnode = Node(subPath, subRemaining, subPathLength, subRM);

   return subnode;
}

double Node::lowerBound() const{
   double lb = pathLength;
   for (unsigned int i = 0; i < rowMinimums.size(); ++i)
      lb += rowMinimums[i];

   return lb;
}

double Node::getPathLength() const{
   return pathLength;
}

Path Node::getPath() const{
   return path;
}

bool Node::operator < (const Node& rn) const{
   return (lowerBound() < rn.lowerBound());
}
