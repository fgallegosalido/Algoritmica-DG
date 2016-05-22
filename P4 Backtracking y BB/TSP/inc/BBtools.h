#ifndef _BBTOOLS_H_
#define _BBTOOLS_H_

#include <vector>
using namespace std;

class Path{
private:
   vector<Point> path;
public:
   Path();
   Path(const Path& p);

   Path getPath() const;
   double getLength() const;

   void addPoint(const Point& p);
   Point getLastPoint() const;
};

class DistanceMatrix{
private:
   double** D;
   int dimension;
public:
   DistanceMatrix(const int& n);
   DistanceMatrix(double** m, const int& n);
   DistanceMatrix Submatrix(const int& m, const int& n);

   vector<double> rowMinimums() const;
   double PartialBound() const; // Cota inferior parcial por defecto (mínimo de cada fila)
   double PartialBound2(); //Cota propuesta por Francisco
   double PartialBound3(); //Cota propuesta por Francisco
};

#endif
