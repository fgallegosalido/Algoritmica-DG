#!/bin/bash

cd ..
make
contador=3
mkdir DatosGraficas
mkdir Graficas
cd Script

printf "" > ../DatosGraficas/tiempos.dat
printf "" > ../DatosGraficas/longitud.dat
printf "" > ../DatosGraficas/nodos.dat
printf "" > ../DatosGraficas/colaMaxima.dat
printf "" > ../DatosGraficas/cortes.dat

# La variable $i llevará cada fichero de prueba, y $j el tipo de poda

for i in `seq 3 1 13`; do
   printf "$contador" >> ../DatosGraficas/longitud.dat
   printf "$contador" >> ../DatosGraficas/nodos.dat
   printf "$contador" >> ../DatosGraficas/colaMaxima.dat
   printf "$contador" >> ../DatosGraficas/cortes.dat
   printf "$contador" >> ../DatosGraficas/tiempos.dat

   echo "$i..."
   ../bin/main ../datosTSP/$i > ../datosTSP/$contador.tour

   printf " " >> ../DatosGraficas/longitud.dat
   printf " " >> ../DatosGraficas/nodos.dat
   printf " " >> ../DatosGraficas/colaMaxima.dat
   printf " " >> ../DatosGraficas/cortes.dat
   printf " " >> ../DatosGraficas/tiempos.dat

   cat "./data.dat" | cut -d" " -f1 >> ../DatosGraficas/longitud.dat
   cat "./data.dat" | cut -d" " -f2 >> ../DatosGraficas/nodos.dat
   cat "./data.dat" | cut -d" " -f3 >> ../DatosGraficas/colaMaxima.dat
   cat "./data.dat" | cut -d" " -f4 >> ../DatosGraficas/cortes.dat
   cat "./data.dat" | cut -d" " -f5 >> ../DatosGraficas/tiempos.dat


   let contador=$contador+1
done

# gnuplot graficaLongitud.gp
gnuplot graficaNodos.gp
gnuplot graficaColaMaxima.gp
gnuplot graficaCortes.gp

# gnuplot graficaTiempos ...
# f(x)=a*gamme(argumento1)
# fit f(x) "../DatosGraficas/....dat" via a
