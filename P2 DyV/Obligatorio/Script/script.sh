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
   ./a.out $nelementos 10 1
   ./a.out $nelementos 110 1
   ./a.out $nelementos 210 1
   ./a.out $nelementos 310 1
   ./a.out $nelementos 410 1
   ./a.out $nelementos 510 1
   ./a.out $nelementos 610 1
   ./a.out $nelementos 710 1
   ./a.out $nelementos 810 1
   ./a.out $nelementos 910 1
   echo $nelementos
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
exit 0
