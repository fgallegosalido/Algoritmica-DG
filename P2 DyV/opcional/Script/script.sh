#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Uso: $0 <nombre>"
    exit 1
fi

mkdir ../Graficas 2> /dev/null
mkdir ../Datos 2> /dev/null

# Fuerza bruta
g++ -std=c++11 ../src/fuerza_bruta.cpp
nelementos=10
echo "" > datos.dat
while [ $nelementos -lt 5000 ]; do
    ./a.out $nelementos >> datos.dat
    let nelementos=nelementos+10
done
gnuplot ./gnuplot/fuerza_bruta.gp

mv grafica.jpeg ../Graficas/fuerza_bruta_$1.jpeg
mv datos.dat ../Datos/fuerza_bruta_$1.dat
mv fit.log ../Datos/fit_fuerza_bruta_$1.log
echo "Fuerza bruta completado"

# DyV
g++ -std=c++11 ../src/dyv.cpp
nelementos=10
echo "" > datos.dat
while [ $nelementos -lt 5000 ]; do
    ./a.out $nelementos >> datos.dat
    let nelementos=nelementos+10
done
gnuplot ./gnuplot/dyv.gp

mv grafica.jpeg ../Graficas/dyv_$1.jpeg
mv datos.dat ../Datos/dyv_$1.dat
mv fit.log ../Datos/fit_dyv_$1.log
echo "DyV completado"
