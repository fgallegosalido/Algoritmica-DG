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

class Graph{
  private:
    double** matrix; // matrix nxn
    Point* points;
    int size;

      // Calcula la longitud del recorrido definido por la lista
    double calcular_longitud(list<int> &lista){
      double ret = 0;
      list<int>::iterator next;

      for (auto it=lista.begin(); it!=lista.end(); ++it){
        next = it;
        ++next;
        if (next==lista.end()) next=lista.begin();

        ret += matrix[*it][*next];
      }

      return ret;
    }

    // Función que para un punto dado busca la posición que minimiza el recorrido,
    // y devuelve la longitud mínima para dicho punto y el iterador que la genera
    pair<double, list<int>::iterator> buscar_posicion(list<int> &lista, int nuevo){
      pair<double, list<int>::iterator> ret;
      list<int>::iterator aux, aux2;
      double length;
      double original_length = calcular_longitud(lista);

      for (auto it = lista.begin(); it != lista.end(); ++it){
        if (it==lista.begin()){
          aux = lista.end();
          --aux;
          ret.first = original_length - matrix[*aux][*it];
          lista.insert(it, nuevo);
          ret.first = ret.first + matrix[*(lista.begin())][*it] + matrix[*aux][*(lista.begin())];
          it = ret.second = lista.erase(it);
        }
        else{
          aux = it;
          --aux;
          length = original_length - matrix[*it][*aux];
          lista.insert(it, nuevo);
          aux2 = it;
          --aux2;
          length = length + matrix[*aux][*aux2] + matrix[*aux2][*it];
          if (length < ret.first){
            ret.first = length;
            ret.second = it;
          }
          lista.erase(aux2);
        }
      }

      return ret;
    }

    // Función que busca el punto que genera el recorrido menor para el recorrido que se le pasa
    // y devuelve el índice del punto y el iterador que apunta a donde se inserta
    pair<int, list<int>::iterator> buscar_punto(list<int> &lista, bool* usados){
      pair<int, list<int>::iterator> ret;
      pair<double, list<int>::iterator> aux;
      bool can_compare = false;
      double minimo;

      // Vamos comprobando cada punto y nos quedamos al final con el mejor
      for (int i=0; i<size; ++i){
        if (!usados[i]){
          if (!can_compare){
            can_compare = true;
            aux = buscar_posicion(lista, i);

            ret.first = i;
            ret.second = aux.second;
            minimo = aux.first;
          }
          else{
            aux = buscar_posicion(lista, i);
            if (aux.first < minimo){
              ret.first = i;
              ret.second = aux.second;
              minimo = aux.first;
            }
          }
        }
      }
      return ret;
    }

   public:

    Graph(Point* coordenadas, int n){
      if ( n > 0 ){
        points = new Point[n];
        for (int i=0; i<n; ++i)
          points[i] = coordenadas[i];

        matrix = new double*[n];

        for (int i=0; i<n; ++i)
          matrix[i] = new double[n];
        for (int i=0; i<n; ++i){
          for (int j=i; j<n; ++j)
            matrix[i][j] = matrix[j][i] = coordenadas[i].Distance(coordenadas[j]);
        }
        size = n;
      }
      else{
        size = 0;
        points = NULL;
        matrix = NULL;
      }
    }

    ~Graph(){
      if ( size > 0 ){
        for (int i=0; i<size; ++i)
          delete [] matrix[i];
        delete [] matrix;
      }
    }

    // Acceso a los datos miembro
    Point getPoint(const int &i) const{
      Point p;
      if ( i >= 0 )
        p = points[i];

      return p;
    }

    int getSize() const{
      return size;
    }

    int* insertion(double &tam){
      int* permutation = new int[size];
      list<int> recorrido;      // Lista que controla el recorrido parcial
      bool* usados = new bool[size];    // Vector de bits que controla los puntos que ya he usado.
      int este = 0, oeste, norte;   // Inicializamos el este al índice 0

      // Inicializamos el vector de booleanos
      for (int i=0; i<size; ++i)
        usados[i] = false;

      // Buscamos el que está más al este
      for (int i=1; i<size; ++i)
        if (points[este].getX()<points[i].getX()) este = i;
      usados[este] = true;
      recorrido.push_back(este);

      oeste = (este==0)?1:0;    // Inicializamos el oeste al menor índice posible

      // Buscamos el que está más al oeste
      for (int i=0; i<size; ++i)
        if (points[oeste].getX()>points[i].getX() && i!=este) oeste = i;
      usados[oeste] = true;
      recorrido.push_back(oeste);

      // Inicializamos el norte al menor índice posible
      if (este>0 && oeste>0) norte = 0;
      else if ((este==0 && oeste>1) || (oeste==0 && este>1)) norte = 1;
      else norte = 2;

      // Buscamos el que está más al norte
      for (int i=0; i<size; ++i)
        if (points[norte].getY()<points[i].getY() && i!=este && i!=oeste) norte = i;
      usados[norte] = true;
      recorrido.push_back(norte);

      pair<int, list<int>::iterator> insertor;

      // Vamos creando la lista del recorrido
      while (recorrido.size() < size){
        insertor = buscar_punto(recorrido, usados);
        recorrido.insert(insertor.second, insertor.first);
        usados[insertor.first] = true;
      }

      for (int i=0; i<size; ++i){
        permutation[i] = recorrido.front();
        recorrido.pop_front();
      }

      list<int> l;
      for(int i=0; i<size; ++i)
        l.push_back(permutation[i]);
      tam = calcular_longitud(l);

      return permutation;
    }
};

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
  bool exit = false;
  if (argc != 2){
    cerr << "Formato: " << argv[0] << " <fichero.tsp>" << endl;
    return -1;
  }

  if (exit)
    return -1;

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
