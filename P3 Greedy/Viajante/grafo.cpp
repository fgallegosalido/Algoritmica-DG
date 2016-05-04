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

      int* concretNearestNeighbour(int initial) const{
         int *neighbours = new int[size-1];
         int index_distance[2][size-1];
         int index, distance;

         for (int i=0; i<size; ++i){
            if (i < initial){
               index_distance[0][i] = i;
               index_distance[1][i] = matrix[i][initial];
               // Equivalente a matrix[initial][i], matrix simétrica
            }
            else if (i > initial){
               index_distance[0][i-1] = i;
               index_distance[1][i-1] = matrix[i][initial];
            }
         }

         for (int i=0; i<size; ++i){
            for (int j=i; j<size && (index_distance[1][j] < index_distance[1][j-1]) ; ++j){
               index = j-1;
               distance = index_distance[1][j-1];
               index_distance[0][j-1] = index_distance[0][j];
               index_distance[1][j-1] = index_distance[1][j];
               index_distance[0][j] = index;
               index_distance[1][j] = distance;
            }
         }

         for (int i=0; i<(size-1); ++i)
            neighbours[i] = index_distance[0][i];

         return neighbours;
      }

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
        double length;

        for (auto it = lista.begin(); it != lista.end(); ++it){
          if (it==lista.begin()){
            ret.second = it;
            lista.insert(it, nuevo);
            ret.first = calcular_longitud(lista);
            --it;
            it = lista.erase(it);
          }
          else{
            lista.insert(it, nuevo);
            length = calcular_longitud(lista);
            if (length < ret.first){
              ret.first = length;
              ret.second = it;
            }
            --it;
            it = lista.erase(it);
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

   class Edge{
      private:
         int first, second;
         double length;
      public:
         Edge(int a, int b, double ab):first(a), second(b), length(ab){}
         Edge():first(0), second(0), length(0){}

         void setEdge(int a, int b, double ab){
            first = a;
            second = b;
            length = ab;
         }

         int getFirst() const{
            return first;
         }

         int getSecond() const{
            return second;
         }

         int getLength() const{
            return length;
         }


         Edge& operator=(const Edge &other){
            if (this != &other){
               first = other.getFirst();
               second = other.getSecond();
               length = other.getLength();
            }
            return *this;
         }

         bool operator<(const Edge &other){
            return (length < other.getLength());
         }
         bool operator>=(const Edge &other){
            return ( !(length < other.getLength()) );
         }

   };

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

      // Funciones para los ciclos hamiltonianos

      int* nearestNeighbour(){
        int* order = new int[size];
        int* near;
        bool found = false, repeat;
        order[0] = 0;
        order[1] = concretNearestNeighbour(0)[0];

        for (int i=2; i<size; ++i){
            near = concretNearestNeighbour(i-1); // Devuelve un vector de size-1 elementos
            for (int j=0; j<(size-1) && !found; ++j){
                repeat = false;
                for (int k=0; k<i && !repeat; ++k){
                    if (near[j] == order[i])
                        repeat = true;
                }

                if (!repeat){
                    order[i] = near[j];
                    found = true;
                }
            }
        }

        return order;
      }

      int* minimizingEdges(){
          vector< list<Edge> > paths;
          vector<Edge> orderedEdges;
          list<Edge> aux;
          Edge item, temp;
          int i, j, k;

          for (i=0; i<size; ++i){
             for (j=0; j<size; ++j){
                item.setEdge(i, j, matrix[i][j]);
                orderedEdges.push_back(item); // size*size elementos
             }
          }

          // Heapsort
          for(k=size*size; k>0; --k){
             for(i=1; i<=k; ++i){
                item = orderedEdges[i];
                j = i/2;
                while(j>0 && orderedEdges[j]<item){
                    orderedEdges[i] = orderedEdges[j];
                    i = j;
                    j = j/2;
                }
                orderedEdges[i] = item;
             }
             temp = orderedEdges[1];
             orderedEdges[1] = orderedEdges[k];
             orderedEdges[k] = temp;
          }
          // Comprobar que ordena
<<<<<<< HEAD


          /*
           Lo que haremos será tener un vector de vectores de aristas
           En cada vector de aristas se meterán las aristas ordenadas, de forma que
           el primer elemento indique el principio (principio y final equivalentes salvo
           permutaciones) y el último indique el final del camino. Esto nos ayudará a
           obtener una función que compruebe si se forman ciclos con una eficiencia constante.
           */
          paths.push_back(aux);
          paths[0].push_back(orderedEdges[0]); // Insertamos la arista más corta como el primer camino

         /*
            Este vector de códigos nos informará del estado de cada vértice.
            Definimos estado como el lugar que ocupa el vértice en nuestro algoritmo.
            Vease:
            Inicialmente los vértices tienen estado -1, significa que no han sido usados aún por el algoritmo
            Si se inserta una nueva arista, su primer vértice (inicio del camino) pasará al estado
               1+10*posicion
            siendo posicion el lugar que ocupa dentro del vector de listas (es una forma de diferenciar
            los diferentes caminos, necesaria).
            De esta forma si (estado1/10 == estado2/10) sabemos que los vértices están en el mismo camino.
            El segundo vértice (último elemento) tendrá el estado
               2+10*posicion
            Si hubiese vértices entre el principio y el final (cuando tenemos más de una arista)
            los vértices intermedios tendrían estado
               3+10*posicion
            Estos casos nos permiten saber directamente al insertar una arista si forma ciclo.
          */

         int *codes = new int[size];
         for (int i=0; i<size; ++i)
            codes[i] = -1;
         codes[ orderedEdges[0].getFirst()  ] = 01; // 0 por que está en paths[0]
         codes[ orderedEdges[0].getSecond() ] = 02;

         /*
            Denotando como "one" y "two" los códigos de los vértices de la arista que queremos insertar.

            - Caso 1(bien): Ninguno está. En este caso se añadiría un nuevo vector de vectores
                           con una sola arista que nos indicaría que se ha creado un nuevo camino,
                           en lugar de extender uno anterior.
            #-----------#  *--*
            Código: ((one == -1) && (two == -1))

            - Caso 2(bien): Está uno y el otro está libre
              #-----------*--*
            Código: ((one%10 == 1) && (two == -1) || (one%10 == 2) && (two == -1)
                     (two%10 == 1) && (one == -1) || (two%10 == 2) && (one == -1) )

            - Caso 3(bien): La arista une caminos, están los dos
               #-----------*--*----------------------#
            Meteremos los elementos de la segunda lista de aristas en la primera
            Código:( ((one%10 == 1) && (two%10 == 1) && (one/10 != two/10)) ||
                     ((one%10 == 2) && (two%10 == 2) && (one/10 != two/10)) ||
                     ((one%10 == 1) && (two%10 == 2) && (one/10 != two/10)) ||
                     ((one%10 == 2) && (two%10 == 1) && (one/10 != two/10)) )

            - Caso 4(mal): Está uno en mitad
            #-----*----#
                  |
                  *
            Código: ((one == -1 && two%10 == 3) || (two == -1 && one%10 == 3))

            - Caso 5(mal): Están los dos y forma ciclo
            +------*
            |      |
            +------*
            Código: (((one%10 == 1) || (one%10 == 2)) && ((two%10 == 1) || (two%10 == 2)) && (one/10 == two/10))

            Al conocer todos los posibles casos solamente nos interesan los 3 que hacen
            que tengamos en cuenta dicha arista en nuestro algoritmo. Cuando insertemos una arista
            tendremos que modificar el estado de los vértices pertinentes
         */

         int count, index, one, two, end;
         int codeone, codetwo;
         Edge edge;
         end = size*size;
         count = index = 1; // Hemos insertado ya una arista.

         while (count < end && index < size){
            // orderedEdges[count], index es la cantidad de aristas que hemos insertado.
            one = orderedEdges[count].getFirst();
            two = orderedEdges[count].getSecond();
            codeone = codes[ one ];
            codetwo = codes[ two ];

            if ( (codeone == -1) && (codetwo == -1) ){
               // Caso 1 #-----------#  *--*
               paths.push_back(aux); // Insertamos un vector vacío y lo modificamos
               paths[ paths.size()-1 ].push_back( orderedEdges[count] );
               codes[ one ] = 10*(paths.size()-1) + 1;
               codes[ two ] = 10*(paths.size()-1) + 2;
               ++index;
            }
            else if ( (codeone%10 == 1) && (codetwo == -1) ){
               // Caso 2 #-----------*--*
               edge.setEdge( two, one, matrix[one][two]);
               paths[ codeone/10 ].push_front( edge );
               codes[ one ] = codeone/10 + 3;
               codes[ two ] = codeone/10 + 1;
               ++index;
            }
            else if ( (codeone%10 == 2) && (codetwo == -1) ){
               // Caso 2 #-----------*--*
               paths[ codeone/10 ].push_back( orderedEdges[count] );
               codes[ one ] = codeone/10 + 3;
               codes[ two ] = codeone/10 + 2;
               ++index;
            }
            else if ( (codetwo%10 == 1) && (codeone == -1) ){
               // Caso 2 #-----------*--*
               paths[ codetwo/10 ].push_front( orderedEdges[count] );
               codes[ one ] = codetwo/10 + 1;;
               codes[ two ] = codetwo/10 + 3;
               ++index;
            }
            else if ( (codetwo%10 == 2) && (codeone == -1) ){
               // Caso 2 #-----------*--*
               edge.setEdge( two, one, matrix[one][two]);
               paths[ codetwo/10 ].push_back( edge );
               codes[ one ] = codetwo/10 + 2;
               codes[ two ] = codetwo/10 + 3;
               ++index;
            }
            else if ( (codeone%10 == 1) && (codetwo%10 == 1) && (codeone/10 != codetwo/10) ){
               // Caso 3 #-----------*--*----------------------#
               if ( one == paths[ codeone/10 ].front().getFirst() ){
                  edge.setEdge( two, one, matrix[one][two]);
                  paths[ codeone/10 ].push_front( edge );
                  codes[ one ] = codes[ two ] = codeone/10 + 3;
               }
               else{ // ( two == paths[ codeone/10 ].front().getFirst() )
                  paths[ codeone/10 ].push_front( orderedEdges[count] );
                  codes[ one ] = codes[ two ] = codeone/10 + 3;
               }

               while(!paths[ codetwo/10 ].empty()){
                  int first = paths[codetwo/10].front().getSecond();
                  int second = paths[codetwo/10].front().getFirst();
                  edge.setEdge( first, second, matrix[first][second] );
                  paths[ codeone/10 ].push_front( edge );
                  paths[ codetwo/10 ].pop_front();
                  // Cambiamos la decena, ya que ha cambiado de camino
                  codes[ paths[ codeone/10 ].front().getSecond() ] = codeone/10 + 3;
               }
               codes[ paths[ codeone/10 ].front().getFirst() ] = codeone/10 + 1;

               ++index;
            }
            else if ( (codeone%10 == 2) && (codetwo%10 == 2) && (codeone/10 != codetwo/10) ){
               // Caso 3 #-----------*--*----------------------#
               if ( one == paths[ codeone/10 ].back().getSecond() ){
                  paths[ codeone/10 ].push_back( orderedEdges[count] );
                  codes[ one ] = codes[ two ] = codeone/10 + 3;
               }
               else{ // ( two == paths[ codeone/10 ].back().getSecond() )
                  int first = orderedEdges[count].getSecond();
                  int second = orderedEdges[count].getFirst();

                  edge.setEdge( first, second, matrix[first][second] );
                  paths[ codeone/10 ].push_back( edge );
                  codes[ one ] = codes[ two ] = codeone/10 + 3;
               }

               while(!paths[ codetwo/10 ].empty()){
                  int first = paths[codetwo/10].back().getSecond();
                  int second = paths[codetwo/10].back().getFirst();
                  edge.setEdge( first, second, matrix[first][second]);
                  paths[ codeone/10 ].push_back( edge );
                  paths[ codetwo/10 ].pop_front();
                  // Cambiamos la decena, ya que ha cambiado de camino
                  codes[ paths[ codeone/10 ].back().getFirst() ] = codeone/10 + 3;
               }
               codes[ paths[ codeone/10 ].back().getSecond() ] = codeone/10 + 2;

               ++index;
            }
            else if ( (codeone%10 == 1) && (codetwo%10 == 2) && (codeone/10 != codetwo/10) ){
               // Caso 3 #-----------*--*----------------------#
               paths[ codeone/10 ].push_front( orderedEdges[count] );
               codes[ one ] = codes[ two ] = codeone/10 + 3;

               while(!paths[ codetwo/10 ].empty()){
                  paths[ codeone/10 ].push_front( paths[codetwo/10].back() );
                  paths[ codetwo/10 ].pop_back();
                  // Cambiamos la decena, ya que ha cambiado de camino
                  codes[ paths[ codeone/10 ].front().getSecond() ] = codeone/10 + 3;
               }
               codes[ paths[ codeone/10 ].front().getFirst() ] = codeone/10 + 1;
               ++index;
            }
            else if ( (codeone%10 == 2) && (codetwo%10 == 1) && (codeone/10 != codetwo/10) ){
               // Caso 3 #-----------*--*----------------------#
               paths[ codeone/10 ].push_back( orderedEdges[count] );
               codes[ one ] = codes[ two ] = codeone/10 + 3;

               while(!paths[ codetwo/10 ].empty()){
                  paths[ codeone/10 ].push_back( paths[codetwo/10].front() );
                  paths[ codetwo/10 ].pop_front();
                  // Cambiamos la decena, ya que ha cambiado de camino
                  codes[ paths[ codeone/10 ].back().getFirst() ] =  codeone/10 + 3;
               }
               codes[ paths[ codeone/10 ].back().getSecond() ] =  codeone/10 + 2;
               ++index;
            }

            ++count;
         }

         int *ret = new int[size];
         int lista = codes[0]/10;

         for (int i=0; i<size; ++i){
            ret[i] = paths[lista].front().getFirst();
            paths[lista].pop_front();
         }

         return ret;
      }

      int* insertion(){
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
  if (argc != 3){
    cerr << "Formato: " << argv[0] << " <fichero.tsp>" << " <modo>" << endl;
    cerr << "Modo:\n\t1 --> Vecino más cercano\n\t 2 --> Inserción\n\t3 --> Minimizando aristas" << endl;
    return -1;
  }

  int mode = atoi(argv[2]);

  if ( mode > 3 || mode < 1 ){
    cerr << "Modo incorrecto" << endl;
    cerr << "Modo:\n\t1 --> Vecino más cercano\n\t 2 --> Inserción\n\t3 --> Minimizando aristas" << endl;
    exit = true;
  }

  if (exit)
    return -1;

  srandom(time(0));
  int size;
  int* order;

  Point* points = readPoints(argv[1], size);

  Graph graph(points, size);

  chrono::high_resolution_clock::time_point tbefore, tafter;
  chrono::duration<double> duration;

  tbefore = chrono::high_resolution_clock::now();
  if (mode == 1)
    order = graph.nearestNeighbour();
  else if (mode == 2)
    order = graph.insertion();
  else // mode == 3
    order = graph.minimizingEdges();
  tafter = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::duration<double>>(tafter - tbefore);

  cout << size << "\t" << duration.count() << endl;

  ofstream solution("order.dat");
  for (int i=0; i<size; ++i)
    solution << order[i] << " " << graph.getPoint(order[i]).getX() << " " << graph.getPoint(order[i]).getY() << endl;


}
