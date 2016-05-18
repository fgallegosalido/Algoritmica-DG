#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <list>
#include "../src/point.cpp"
using namespace std;

class Graph{
  private:
    double** matrix; // matrix nxn
    Point* points;
    int size;

    double calcular_longitud(list<int> &lista);
    pair<double, list<int>::iterator> buscar_posicion(list<int> &lista, int nuevo);
    pair<int, list<int>::iterator> buscar_punto(list<int> &lista, bool* usados);

   public:

    Graph(Point* coordenadas, int n);
    ~Graph();
    Point getPoint(const int &i) const;
    int getSize() const{return size;}
    int* insertion(double &tam);
    int* TSPConBB(double &tam);
};

#endif
