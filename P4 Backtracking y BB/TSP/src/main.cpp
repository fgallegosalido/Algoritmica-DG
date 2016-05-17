#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "grafo.h"
using namespace std;

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
  
  if (argc != 2){
    cerr << "Formato: " << argv[0] << " <fichero.tsp>" << endl;
    return -1;
  }

  srandom(time(0));
  int size;
  int* order;
  double distance;

  Point* points = readPoints(argv[1], size);

  Graph graph(points, size);

  chrono::high_resolution_clock::time_point tbefore, tafter;
  chrono::duration<double> duration;

  tbefore = chrono::high_resolution_clock::now();

  order = graph.insertion(distance);

  tafter = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::duration<double>>(tafter - tbefore);

  cout << size << " " << duration.count() << endl;

  //ofstream solution("rd100_insertion.dat");
  //for (int i=0; i<size; ++i)
  // solution << graph.getPoint(order[i]).getX() << " " << graph.getPoint(order[i]).getY() << endl;
  cout << distance << endl;

}
