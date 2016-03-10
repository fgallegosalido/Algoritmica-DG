#!/bin/bash

if [ $# -ne 2 ] 
then 
    echo "Uso: $0 <nombre>"
    exit(1)
fi

rm *~
rm ./gnuplot/*~
rm ../src/*~
rm ../Graficas/Burbuja/*$1*
rm ../Graficas/Burbuja/Datos/*$1*
rm ../Graficas/Fibonacci/*$1*
rm ../Graficas/Fibonacci/Datos/*$1*
rm ../Graficas/Floyd/*$1*
rm ../Graficas/Floyd/Datos/*$1*
rm ../Graficas/Hanoi/*$1*
rm ../Graficas/Hanoi/Datos/*$1*
rm ../Graficas/Heapsort/*$1*
rm ../Graficas/Heapsort/Datos/*$1*
rm ../Graficas/Insercion/*$1*
rm ../Graficas/Insercion/Datos/*$1*
rm ../Graficas/Mergesort/*$1*
rm ../Graficas/Mergesort/Datos/*$1*
rm ../Graficas/Quicksort/*$1*
rm ../Graficas/Quicksort/Datos/*$1*
rm ../Graficas/Seleccion/*$1*
rm ../Graficas/Seleccion/Datos/*$1*


