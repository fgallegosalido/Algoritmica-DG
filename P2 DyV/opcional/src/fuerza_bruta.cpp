#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;



int inversiones(vector<int> v){
  int count = 0;
  int size = v.size();
  for (int i=0; i < size; i++)
    for (int j=i+1; j < size; j++)
      if (v[i] > v[j])
        count++;

  return count;
}


int main(int argc, char** argv){
  if (argc < 2){
    cerr << "Formato " << argv[0] << " num_elem" << endl;
    return -1;
  }

  int n = atoi(argv[1]);
  vector<int> rankings(n);
  srandom(time(0));
  for (int i=0; i < n; i++){
    rankings[i] = i;
  }
  random_shuffle(rankings.begin(), rankings.end());

  chrono::high_resolution_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;

  tantes = chrono::high_resolution_clock::now();
  inversiones(rankings);
  tdespues = chrono::high_resolution_clock::now();
  transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);

  cout << n << " " << transcurrido.count() << endl;
}
