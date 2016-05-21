#!/bin/bash

MIN=3
MAX=27
SUM=1

g++ -std=c++11 ../src/equipos.cpp -o equipos
printf "" > ../Datos/sinEquilibrar.dat
printf "" > ../Datos/equilibrar.dat
printf "" > ../Datos/distancias.dat
printf "" > ../Datos/separacion.dat

iterador=$MIN
while [ $iterador -lt $MAX ]; do
   ./equipos $iterador 0 >> ../Datos/sinEquilibrar.dat # Genera distancia.txt y separacion.txt
   printf "$iterador "   >> ../Datos/distancias.dat
   cat "distancia.txt"   >> ../Datos/distancias.dat

   printf "$iterador "   >> ../Datos/separacion.dat
   cat "separacion.txt"  >> ../Datos/separacion.dat


   ./equipos $iterador 1 >> ../Datos/equilibrar.dat # Genera distancia.txt y separacion.txt
   printf " "            >> ../Datos/distancias.dat
   cat "distancia.txt"   >> ../Datos/distancias.dat
   echo ""               >> ../Datos/distancias.dat

   printf " "            >> ../Datos/separacion.dat
   cat "separacion.txt"  >> ../Datos/separacion.dat
   echo ""               >> ../Datos/separacion.dat


   let iterador=$iterador+$SUM
   echo "$iterador"
done
echo "Terminado"

gnuplot ./equilibrar.gp
gnuplot ./sinEquilibrar.gp
gnuplot ./comparativaTiempos.gp
gnuplot ./comparativaDistancias.gp
gnuplot ./comparativaSeparacion.gp

rm -f distancia.txt separacion.txt equipos fit.log
