#!/bin/bash

if [ $# -ne 2 ] 
then 
    echo "Uso: $0 <nombre>"
    exit 1
fi

# HEAPSORT
g++ -std=c++11 ../src/heapsort.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 10000 ]; do
    ./a.out $nelementos >> datos.dat    
    let nelementos=nelementos+1000 
done

gnuplot ./gnuplot/heapsort.gp # Salida: "fichero.jpeg"

mv fichero.jpeg ../Graficas/Heapsort/heapsortO0_$1.jpeg
mv datos.dat ../Graficas/Heapsort/Datos/heapsortO0_$1.dat
echo "Heapsort completado\n"


# MERGESORT
g++ -std=c++11 ../src/mergesort.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 10000 ]; do
    ./a.out $nelementos >> datos.dat    
    let nelementos=nelementos+1000 
done

gnuplot ./gnuplot/mergesort.gp # Salida: "fichero.jpeg"

mv fichero.jpeg ../Graficas/Mergesort/mergesortO0_$1.jpeg
mv datos.dat ../Graficas/Mergesort/Datos/mergesortO0_$1.dat
echo "Mergesort completado\n"


# INSERCION
g++ -std=c++11 ../src/insercion.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 10000 ]; do
    ./a.out $nelementos >> datos.dat    
    let nelementos=nelementos+1000 
done

gnuplot ./gnuplot/insercion.gp # Salida: "fichero.jpeg"

mv fichero.jpeg ../Graficas/Insercion/insercionO0_$1.jpeg
mv datos.dat ../Graficas/Insercion/Datos/insercionO0_$1.dat
echo "Insercion completado\n"


# SELECCION
g++ -std=c++11 ../src/seleccionn.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 10000 ]; do
    ./a.out $nelementos >> datos.dat    
    let nelementos=nelementos+1000 
done

gnuplot ./gnuplot/insercion.gp # Salida: "fichero.jpeg"

mv fichero.jpeg ../Graficas/Seleccion/seleccionO0_$1.jpeg
mv datos.dat ../Graficas/Seleccion/Datos/seleccionO0_$1.dat
echo "Seleccion completado\n"


# QUICKSORT
g++ -std=c++11 ../src/quicksort.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 10000 ]; do
    ./a.out $nelementos >> datos.dat    
    let nelementos=nelementos+1000 
done

gnuplot ./gnuplot/quicksort.gp # Salida: "fichero.jpeg"

mv fichero.jpeg ../Graficas/Quicksort/quicksortO0_$1.jpeg
mv datos.dat ../Graficas/Quicksort/Datos/quicksortO0_$1.dat
echo "Quicksort completado\n"


# BURBUJA
g++ -std=c++11 ../src/burbuja.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 10000 ]; do
    ./a.out $nelementos >> datos.dat    
    let nelementos=nelementos+1000 
done

gnuplot ./gnuplot/burbuja.gp # Salida: "fichero.jpeg"

mv fichero.jpeg ../Graficas/Burbuja/burbujaO0_$1.jpeg
mv datos.dat ../Graficas/Burbuja/Datos/burbujaO0_$1.dat
echo "Burbuja completado\n"


# FIBONACCI
g++ -std=c++11 ../src/fibonacci.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 100000 ]; do
    ./a.out $nelementos >> datos.dat    
    let nelementos=nelementos+100
done

gnuplot ./gnuplot/fibonacci.gp # Salida: "fichero.jpeg"

mv fichero.jpeg ../Graficas/Fibonacci/fibonacciO0_$1.jpeg
mv datos.dat ../Graficas/Fibonacci/Datos/fibonacciO0_$1.dat
echo "Fibonacci completado\n"


# HANOI
g++ -std=c++11 ../src/hanoi.cpp
nelementos=3
echo "" > datos.dat
while [ $nelementos -lt 35 ]; do
    ./a.out $nelementos >> datos.dat    
    let nelementos=nelementos+1
done

gnuplot ./gnuplot/hanoi.gp # Salida: "fichero.jpeg"

mv fichero.jpeg ../Graficas/Hanoi/hanoiO0_$1.jpeg
mv datos.dat ../Graficas/Hanoi/Datos/hanoiO0_$1.dat
echo "Hanoi completado\n"


# FLOYD
g++ -std=c++11 ../src/floyd.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 100000 ]; do
    ./a.out $nelementos >> datos.dat    
    let nelementos=nelementos+100
done

gnuplot ./gnuplot/floyd.gp # Salida: "fichero.jpeg"

mv fichero.jpeg ../Graficas/Floyd/floydO0_$1.jpeg
mv datos.dat ../Graficas/Floyd/Datos/floydO0_$1.dat
echo "Fibonacci completado\n"

rm *~
rm datos.dat
rm a.out


