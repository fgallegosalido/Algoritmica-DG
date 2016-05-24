#!/bin/bash

cd ..
make
contador=0
mkdir DatosGraficas
mkdir Graficas
cd Script

printf "" > ../DatosGraficas/tiempos0.dat
printf "" > ../DatosGraficas/tiempos1.dat
printf "" > ../DatosGraficas/tiempos2.dat
printf "" > ../DatosGraficas/longitud.dat
printf "" > ../DatosGraficas/nodos.dat
printf "" > ../DatosGraficas/colaMaxima.dat
printf "" > ../DatosGraficas/cortes.dat

# La variable $i llevará cada fichero de prueba, y $j el tipo de poda

for i in `ls ../datosTSP`; do
   printf "$contador" >> ../DatosGraficas/longitud.dat
   printf "$contador" >> ../DatosGraficas/nodos.dat
   printf "$contador" >> ../DatosGraficas/colaMaxima.dat
   printf "$contador" >> ../DatosGraficas/cortes.dat
   printf "$contador" >> ../DatosGraficas/tiempos.dat

   for j in `seq 0 2`;do
      ./bin/main $i $j
      # No estoy seguro de como manejar el size(?)

      printf " " >> ../DatosGraficas/longitud.dat
      printf " " >> ../DatosGraficas/nodos.dat
      printf " " >> ../DatosGraficas/colaMaxima.dat
      printf " " >> ../DatosGraficas/cortes.dat
      printf " " >> ../DatosGraficas/tiempos.dat

      cat "./data.dat" | cut -d " " -f 1 >> ../DatosGraficas/longitud.dat
      cat "./data.dat" | cut -d " " -f 2 >> ../DatosGraficas/nodos.dat
      cat "./data.dat" | cut -d " " -f 3 >> ../DatosGraficas/colaMaxima.dat
      cat "./data.dat" | cut -d " " -f 4 >> ../DatosGraficas/cortes.dat
      cat "./data.dat" | cut -d " " -f 5 >> ../DatosGraficas/tiempos.dat
   done

   let contador=$contador+1
done

# gnuplot graficaLongitud.gp
gnuplot graficaNodos.gp
gnuplot graficaColaMaxima.gp
gnuplot graficaCortes.gp

# gnuplot graficaTiempos ...
# f(x)=a*gamme(argumento1)
# fit f(x) "../DatosGraficas/....dat" via a
