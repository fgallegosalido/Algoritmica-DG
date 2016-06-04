#include "point.h"
using namespace std;


Point::Point(){
   x = y = 0;
}

Point::Point(const double& abscisa, const double& ordenada){
   x = abscisa;
   y = ordenada;
}

Point::Point(const Point &p){
   x = p.getX();
   y = p.getY();
}

double Point::getX() const{
   return x;
}

double Point::getY() const{
   return y;
}

void Point::setX(const double& c){
   x = c;
}

void Point::setY(const double& c){
   y = c;
}

void Point::setXY(const double& c1, const double& c2){
   x = c1;
   y = c2;
}

double Point::distance(const Point &p) const{
   return sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) );
}

Point& Point::operator=(const Point &other){
   if (this != &other){
      x = other.getX();
      y = other.getY();
   }
   return *this;
}

bool Point::operator==(const Point &other) const{
   return (x == other.getX() && y == other.getY());
}

bool Point::operator!=(const Point &other) const{
   return (! (*this == other) );
}

ostream& operator<<(ostream& os, const Point& p){
  os << "(" << p.getX() << ", " << p.getY() << ")";
  return os;
}
