// Función que genera un vector a partir de una matriz, colocando cada vector
// seguido de otro.
int * GeneraVector(int** &matriz, int n_vec, int n_elem){
  int* vector = new int[n_vec*n_elem];

  for (int i=0; i<n_vec; ++i){
    for (int j=0; j<n_elem; ++j){
      vector[i*n_elem+j] = matriz[i][j];
    }
  }

  return vector;
}

// Función que mezcla dos vectores ordenados en uno ordenado
void Merge(int* &vector, int ini, int pivot, int fin){
  int size = fin-ini+1;
  int f_count = 0, s_count = 0;// Contadores de cada vector
  int selected;
  int* aux = new int[size];

  // Hasta que agotemos el tamaño del vector auxiliar
  for (int i=0; i<size; ++i){
    // Si hemos agotado el primer vector:
    if(ini+f_count == pivot){
      selected = vector[pivot+s_count];
      s_count++;
    }
    // Si hemos agotado el segundo:
    else if(s_count+pivot == fin+1){
      selected = vector[ini+f_count];
      f_count++;
    }
    // En cualquier otro caso:
    else{
      // Si el del primer vector es mayor que el del segundo:
      if(vector[ini+f_count] <= vector[pivot+s_count]){
        selected = vector[ini+f_count];
        f_count++;
      }
      // Si es al revés:
      else{
        selected = vector[pivot+s_count];
        s_count++;
      }
    }
    // Asignamos valor a la posición correspondiente del vector
    aux[i] = selected;
  }
  // Asignamos el vector auxiliar al trozo del vector real
  for (int i=0; i<size; ++i){
    vector[ini+i] = aux[i];
  }
  delete[] aux;
}

// Función que hace la partición del vector, teniendo en cuenta donde empieza,
// donde termina y el número de elementos de la partición, y devuelve ese trozo
// ya ordenado
void MergeKPartitions(int* &vector, int n_elem, int ini, int fin){
  int size = fin - ini + 1;
  int partitions = size/n_elem;
  // Caso base: Si hay 2 particiones de igual tamaño, las mezcla
  if(partitions == 2){
    Merge(vector, ini, ini+n_elem, fin);
  }
  // Si hay más de dos particiones:
  else if(partitions > 2){
    int division = ini + (partitions/2)*n_elem; // Cálculo de la división
    MergeKPartitions(vector, n_elem, ini, division-1);  // Llamada al primer conjunto de particiones
    MergeKPartitions(vector, n_elem, division, fin);    // Llamada al segundo conjunto de particiones
    Merge(vector, ini, division, fin);  // Mezclamos los dos conjuntos de particiones, ya ordenados
  }
}

// Función que llama a todo el algoritmo
int* MergeVectors(int** vectors, int n_vec, int n_elem){
  int * full_vector = GeneraVector(vectors, n_vec, n_elem); // Generamos el vector a devolver
  MergeKPartitions(full_vector, n_elem, 0, n_vec*n_elem-1); // Aplicamos la partición y mezcla

  return full_vector;
}
