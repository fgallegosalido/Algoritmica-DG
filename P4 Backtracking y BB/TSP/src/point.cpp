#ifndef _POINT_H_
#define _POINT_H_

#include <cmath>

class Point{
  private:
    double x,y;

  public:
    Point(){
      x = y = 0;
    }

    Point(double abscisa, double ordenada){
      x = abscisa;
      y = ordenada;
    }

    Point(const Point &p){
      x = p.getX();
      y = p.getY();
    }

    double getX() const{
      return x;
    }

    double getY() const{
      return y;
    }

    void setX(const double &c){
      x = c;
    }

    void setY(const double &c){
      y = c;
    }

    void setXY(const double &c1, const double &c2){
      x = c1;
      y = c2;
    }

    double Distance(const Point &p) const{
      return sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) );
    }

    Point& operator=(const Point &other){
      if (this != &other){
        x = other.getX();
        y = other.getY();
      }
      return *this;
    }

    bool operator==(const Point &other) const{
      return (x == other.getX() && y == other.getY());
    }

    bool operator!=(const Point &other) const{
      return (! (*this == other) );
    }
};

#endif
