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

#nelementos=10
#while [ $nelementos -lt 1500 ]; do
#    ./a.out $nelementos 200 3
#    let nelementos=nelementos+50
#done

nelementos=10
nvectores=10
while [ $nelementos -lt 1000 ]; do
   while [ $nvectores -lt 1000 ]; do
       ./a.out $nelementos $nvectores 1
       let nvectores=nvectores+100
   done
    let nelementos=nelementos+100
done


#gnuplot ./gnuplot/fuerza_bruta.gp
#gnuplot ./gnuplot/dyv.gp
#gnuplot ./gnuplot/comparativa.gp

#mv grafica_f.png ../Graficas/fuerza_bruta_nelementos_$1.png
#mv grafica_d.png ../Graficas/dyv_nelementos_$1.png
#mv comparativa.png ../Graficas/comparativa_nelementos_$1.png

mv fuerza_bruta.dat ../Datos/fuerza_bruta_3d_$1.dat
mv dyv.dat ../Datos/dyv_3d_$1.dat

rm fit.log
echo "Terminado"
