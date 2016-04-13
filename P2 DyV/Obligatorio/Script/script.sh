#!/bin/bash

#if [ $# -ne 1 ]
#then
#    echo "Uso: $0 <nombre>"
#    exit 1
#fi

mkdir ../Graficas 2> /dev/null
mkdir ../Datos 2> /dev/null


# El programa generará los datos con fuerza bruta y divide y vencerás simultáneamente
g++ -std=c++11 ../src/mezcla.cpp

nelementos=10
while [ $nelementos -lt 2500 ]; do
    ./a.out $nelementos 200 3
    let nelementos=nelementos+25
done
sleep 1

gnuplot ./gnuplot/fuerza_bruta_nelementos.gp
gnuplot ./gnuplot/dyv_nelementos.gp
gnuplot ./gnuplot/comparativa_nelementos.gp

mv grafica_f.png ../Graficas/fuerza_bruta_nelementos.png
mv grafica_d.png ../Graficas/dyv_nelementos.png
mv comparativa_n.png ../Graficas/comparativa_nelementos.png

mv fuerza_bruta.dat ../Datos/fuerza_bruta_nelementos.dat
mv dyv.dat ../Datos/dyv_nelementos.dat
sleep 1


# Fijamos los elementos
kvectores=10
while [ $kvectores -lt 2500 ]; do
    ./a.out 200 $kvectores 2
    let kvectores=kvectores+25
done
sleep 1

gnuplot ./gnuplot/fuerza_bruta_kvectores.gp
gnuplot ./gnuplot/dyv_kvectores.gp
gnuplot ./gnuplot/comparativa_kvectores.gp

mv grafica_f.png ../Graficas/fuerza_bruta_kvectores.png
mv grafica_d.png ../Graficas/dyv_kvectores.png
mv comparativa_k.png ../Graficas/comparativa_kvectores.png

mv fuerza_bruta.dat ../Datos/fuerza_bruta_kvectores.dat
mv dyv.dat ../Datos/dyv_kvectores.dat



# Datos en 3 dimensiones, número de vectores, elementos del vector, y tiempo del algoritmo
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

   let nelementos=nelementos+100
done
gnuplot ./gnuplot/3d_fuerza_bruta.gp
gnuplot ./gnuplot/3d_dyv.gp

mv grafica_f.png ../Graficas/3d_fuerza_bruta.png
mv grafica_d.png ../Graficas/3d_dyv.png

mv fuerza_bruta.dat ../Datos/3d_fuerza_bruta.dat
mv dyv.dat ../Datos/3d_dyv.dat


rm -f ./a.out
echo "Terminado"
