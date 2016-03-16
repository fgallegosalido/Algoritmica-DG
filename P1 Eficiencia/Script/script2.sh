#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Uso: $0 <nombre>"
    exit 1
fi

# QUICKSORT
g++ -std=c++11 -O2 ../src/quicksort.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 10000 ]; do
    ./a.out $nelementos >> datos.dat
    let nelementos=nelementos+100
done

gnuplot ./gnuplot/quicksort.gp # Salida: "fichero.jpeg"

mkdir ../Graficas/Quicksort 2> /dev/null
mkdir ../Graficas/Quicksort/Datos 2> /dev/null
mv fichero.jpeg ../Graficas/Quicksort/quicksortO2_$1.jpeg
mv datos.dat ../Graficas/Quicksort/Datos/quicksortO2_$1.dat
echo "Quicksort completado"


# BURBUJA
g++ -std=c++11 -O2 ../src/burbuja.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 10000 ]; do
    ./a.out $nelementos >> datos.dat
    let nelementos=nelementos+100
done

gnuplot ./gnuplot/burbuja.gp # Salida: "fichero.jpeg"

mkdir ../Graficas/Burbuja 2> /dev/null
mkdir ../Graficas/Burbuja/Datos 2> /dev/null
mv fichero.jpeg ../Graficas/Burbuja/burbujaO2_$1.jpeg
mv datos.dat ../Graficas/Burbuja/Datos/burbujaO2_$1.dat
echo "Burbuja completado"

# FLOYD
g++ -std=c++11 -O2 ../src/floyd.cpp
nelementos=200
echo "" > datos.dat
while [ $nelementos -lt 1000 ]; do
    ./a.out $nelementos >> datos.dat
    let nelementos=nelementos+10
done

gnuplot ./gnuplot/floyd.gp # Salida: "fichero.jpeg"

mkdir ../Graficas/Floyd 2> /dev/null
mkdir ../Graficas/Floyd/Datos 2> /dev/null
mv fichero.jpeg ../Graficas/Floyd/floydO2_$1.jpeg
mv datos.dat ../Graficas/Floyd/Datos/floydO2_$1.dat
echo "Floyd completado"

rm a.out
rm fit.log
