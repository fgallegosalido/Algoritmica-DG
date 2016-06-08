#ifndef _BBTOOLS_H_
#define _BBTOOLS_H_

#include <list>
#include <vector>
#include <iostream>
#include "point.h"
using namespace std;

class Path{
private:
   list<Point> path;
public:
   Path();
   Path(const Path& p);

   list<Point> getPath() const;
   double getLength() const;

   void addPoint(const Point& p);
   Point getLastPoint() const;

   int getNumPoints();
   int getNumPoints() const;
};

std::ostream& operator<<(std::ostream& os, const Path& p);


class DistanceMatrix{
private:
   double** D;
   int dimension;
public:
   DistanceMatrix(const int& n);
   DistanceMatrix(double** m, const int& n);
   DistanceMatrix Submatrix(const int& m, const int& n);

   vector<double> rowMinimums() const;
   double get(const int& i, const int& j);


   double PartialBound() const; // Cota inferior parcial por defecto (mínimo de cada fila)
   double PartialBound2(); //Cota propuesta por Francisco
   double PartialBound3(); //Cota propuesta por Rubén
};

#endif
