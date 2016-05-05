#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <vector>
#include <list>
using namespace std;

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

double calculardistancia(Point *p, int size){
    double ret = 0;

    for (int i=0; i<size; ++i){
        if (i != (size-1))
            ret += p[i].Distance(p[i+1]);
        else
            ret += p[i].Distance(p[0]);
    }

    return ret;
}

Point* readPoints(char* nombre, int &size){
  ifstream datos;
  string s;
  Point p;
  int n,act;
  double x,y;

  datos.open(nombre);
  if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> n;
    size = n;
    Point* points = new Point[n];
    int i=0;

    while (i<n){
      datos >> act >> x >> y;
      p.setXY(x, y);
	    points[act-1] = p;
	    i++;
    }

    datos.close();
    return points;
  }
  else {
    cout << "Error de Lectura en " << nombre << endl;
  }
}

int main(int argc, char* argv[]){
  cout.precision(15);
  srandom(time(0));
  int size;
  int* order;
  double distance;

  Point* points = readPoints(argv[1], size);

  //cout << size << "\t" << duration.count() << endl;

  //ofstream solution("rd100_insertion.dat");
  //for (int i=0; i<size; ++i)
   // solution << graph.getPoint(order[i]).getX() << " " << graph.getPoint(order[i]).getY() << endl;
   cout << calculardistancia(points,size) << endl;

}

