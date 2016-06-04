#ifndef _POINT_H_
#define _POINT_H_

#include <cmath>
#include <iostream>

class Point{
  private:
    double x,y;

  public:
    Point();
    Point(const double& abscisa, const double& ordenada);
    Point(const Point &p);

    // Getter
    double getX() const;
    double getY() const;

    //Setter
    void setX(const double &c);
    void setY(const double &c);
    void setXY(const double &c1, const double &c2);


    double distance(const Point &p) const;
    Point& operator=(const Point &other);
    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
};

std::ostream& operator<<(std::ostream& os, const Point& p);

#endif
