#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "grafo.h"
using namespace std;

Point* readPoints(char* nombre, int& size){
   ifstream datos;
   string s;
   Point p;
   int n,act;
   double x,y;
   Point* points = NULL;

   datos.open(nombre);
   if (datos.is_open()) {
      datos >> s; // Leo "dimension:"
      datos >> n;
      size = n;
      points = new Point[n];
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
   return points;
}

int main(int argc, char* argv[]){
   cout.precision(15);

   if (argc != 3){
      cerr << "Formato: " << argv[0] << " <fichero.tsp> <0/1/2 cota inferior>" << endl;
      return -1;
   }

   srandom(time(0));
   int size, nodes, queueMaxSize, cuts;
   //int* order;
   double distance;
   Point* points = readPoints(argv[1], size);
   Graph graph(points, size);
   Path path;

   chrono::high_resolution_clock::time_point tbefore, tafter;
   chrono::duration<double> duration;

   tbefore = chrono::high_resolution_clock::now();
   path = graph.TSP_BB(nodes, queueMaxSize, cuts, atoi(argv[2]));
   tafter = chrono::high_resolution_clock::now();

   duration = chrono::duration_cast<chrono::duration<double>>(tafter - tbefore);

   cout << size << " " << duration.count() << endl;

   ofstream data("data.dat");
   data << path.getLength() << " " << nodes << " " << queueMaxSize << " " << cuts << " " << duration.count() << endl;
}
