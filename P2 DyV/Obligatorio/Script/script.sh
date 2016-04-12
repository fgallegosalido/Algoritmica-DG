#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Uso: $0 <nombre>"
    exit 1
fi

mkdir ../Graficas 2> /dev/null
mkdir ../Datos 2> /dev/null

# Fuerza bruta
g++ -std=c++11 ../src/mezcla.cpp

echo "hola\n"
nvectores=10
echo "" > datos.dat
while [ $nvectores -lt 1500 ]; do
    ./a.out 200 $nvectores "kvectores" >> datos.dat
    let nvectores=nvectores+50
done
gnuplot ./gnuplot/fuerza_bruta.gp
gnuplot ./gnuplot/dyv.gp
gnuplot ./gnuplot/comparativa.gp

mv grafica_f.png ../Graficas/fuerza_bruta_kvectores_$1.png
mv grafica_d.png ../Graficas/dyv_kvectores_$1.png
mv comparativa.png ../Graficas/comparativa_kvectores_$1.png

mv fuerza_bruta.dat ../Datos/fuerza_bruta_kvectores_$1.dat
mv dyv.dat ../Datos/dyv_kvectores_$1.dat

mv fit.log /dev/null
echo "Terminado"
