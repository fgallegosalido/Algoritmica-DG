#ifndef _NODE_H_
#define _NODE_H_

#include <queue>
#include <vector>
#include "BBtools.h"
#include "point.h"
using namespace std;

class Node{
private:
   Path path;
   vector<Point> remaining;
   double pathLength;
   vector<double> rowMinimums;
public:
   Node(const Path& p, vector<Point> r, const double& pl, vector<double> rm);
   int numberOfBranches() const;

   //Devuelve el i-ésimo nodo hijo.
   double lowerBound() const;
   Node getSubnode(int& i) const;
   double getPathLength() const;
   Path getPath() const;
   bool operator < (const Node& rn) const;
};

#endif
