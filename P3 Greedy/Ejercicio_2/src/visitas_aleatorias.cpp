#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <list>
using namespace std;



void random_visits(bool* days_open, int P, int R, list<int>& visit_days){
  int k, min_RP;
  for (int i=0; i+R < P; i=k+1){
    min_RP = i+R < P ? i+R : P;
    k = rand() % (min_RP-1-i) + i;  // Entre i e i+R-1
    while (!days_open[k] && k < P && k < i+R)
      k++;
    while (!days_open[k] && k >= i)
      k--;
    visit_days.push_back(k+1);
  }
}


int main(int argc, char** argv){
  if (argc < 2){
    cerr << "Formato: " << argv[0] << " periodo_de_tiempo [r]" << endl;
    return -1;
  }

  srandom(time(0));
  const int P = atoi(argv[1]);
  int R = rand() % (P-2) + 2;
  if (argc > 2) R = atoi(argv[2]);
  bool* days_open = new bool[P];
  int consecutive_falses = 0;
  for (int i=0; i < P; i++){
    days_open[i] = rand() % 2;
    if (days_open[i] == false) consecutive_falses++;
    else consecutive_falses = 0;
    if (consecutive_falses == R){
      days_open[i] = true;
      consecutive_falses = 0;
    }
  }

  chrono::high_resolution_clock::time_point tbefore, tafter;
  chrono::duration<double> duration;
  list<int> visit_days;

  tbefore = chrono::high_resolution_clock::now();
  random_visits(days_open, P, R, visit_days);
  tafter = chrono::high_resolution_clock::now();

  duration = chrono::duration_cast<chrono::duration<double>>(tafter - tbefore);

  #ifndef GP_OUT
    cout << "Dias abierto: ";
    for (int i=0; i < P; i++)
      cout << days_open[i] << " ";
    cout << endl;
    cout << "R = " << R << endl;
    cout << "Dias visita: ";
    for (list<int>::iterator it=visit_days.begin(); it != visit_days.end(); ++it){
      cout << *it << " ";
    }
    cout << endl;
    cout << "Num visitas: " << visit_days.size() << endl;
  #else
    cout << visit_days.size() << " " << duration.count() << endl;
  #endif
}
