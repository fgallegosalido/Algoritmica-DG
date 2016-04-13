#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Uso: $0 <nombre>"
    exit 1
fi

mkdir ../Graficas 2> /dev/null
mkdir ../Datos 2> /dev/null

# Fuerza bruta
g++ -std=c++11 -D GP_OUT ../src/fuerza_bruta.cpp
nelementos=10
echo "" > datos.dat
while [ $nelementos -lt 5000 ]; do
    ./a.out $nelementos >> datos.dat
    let nelementos=nelementos+10
done
gnuplot ./gnuplot/fuerza_bruta.gp

mv grafica.png ../Graficas/fuerza_bruta_$1.png
mv datos.dat ../Datos/fuerza_bruta_$1.dat
mv fit.log ../Datos/fit_fuerza_bruta_$1.log
echo "Fuerza bruta completado"

# DyV
g++ -std=c++11 -D GP_OUT ../src/dyv.cpp
nelementos=10
echo "" > datos.dat
while [ $nelementos -lt 5000 ]; do
    ./a.out $nelementos >> datos.dat
    let nelementos=nelementos+10
done
gnuplot ./gnuplot/dyv.gp

mv grafica.png ../Graficas/dyv_$1.png
mv datos.dat ../Datos/dyv_$1.dat
mv fit.log ../Datos/fit_dyv_$1.log
echo "DyV completado"

# DyV mergesort
g++ -std=c++11 -D GP_OUT ../src/dyv_mergesort.cpp
nelementos=10
echo "" > datos.dat
while [ $nelementos -lt 5000 ]; do
    ./a.out $nelementos >> datos.dat
    let nelementos=nelementos+10
done
gnuplot ./gnuplot/dyv_mergesort.gp

mv grafica.png ../Graficas/dyv_mergesort_$1.png
mv datos.dat ../Datos/dyv_mergesort_$1.dat
mv fit.log ../Datos/fit_dyv_mergesort_$1.log
echo "DyV mergesort completado"

#Comparativa
cd gnuplot
gnuplot comparativa.gp

mv comparativa.png ../../Graficas/comparativa.png
echo "comparativa completada"
cd ..
