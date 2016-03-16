#!/bin/bash

for DIR in `ls Graficas/`; do
  if [ $DIR != Ajustes ] && [ -d Graficas/$DIR ]
    then
    archivo="temporal.gp"

    echo "set terminal jpeg" > $archivo
    echo "set output \"fichero.jpeg\"" >> $archivo
    echo "set title \"Eficiencia $DIR\"" >> $archivo
    echo "set xlabel \"Tamaño del vector\"" >> $archivo
    echo "set ylabel \"Tiempo (s)\"" >> $archivo
    echo "set fit quiet" >> $archivo
    echo "unset key" >> $archivo

    num=0
    dir="Graficas/$DIR/Datos"

    for FILE in `ls $dir`; do
      if [ $DIR == Burbuja ] || [ $DIR == Insercion ] || [ $DIR == Seleccion ]
        then
        echo "f$num(x) = a*x*x+b*x+c" >> $archivo
        echo "fit f$num(x) \"$dir/$FILE\" via a, b, c" >> $archivo
      elif [ $DIR == Mergesort ] || [ $DIR == Quicksort ] || [ $DIR == Heapsort ]
        then
        echo "f$num(x) = a*x*(log(x)/log(2))" >> $archivo
        echo "fit f$num(x) \"$dir/$FILE\" via a" >> $archivo
      elif [ $DIR == Fibonacci ]
        then
        echo "f$num(x) = a*(((1+sqrt(5))/2)**x)" >> $archivo
        echo "fit f$num(x) \"$dir/$FILE\" via a" >> $archivo
      elif [ $DIR == Floyd ]
        then
        echo "f$num(x) = a*x*x*x+b*x*x+c*x+d" >> $archivo
        echo "fit f$num(x) \"$dir/$FILE\" via a, b, c, d" >> $archivo
      elif [ $DIR == Hanoi ]
        then
        echo "f$num(x) = a*(2**x)" >> $archivo
        echo "fit f$num(x) \"$dir/$FILE\" via a" >> $archivo
      fi

      let num=num+1
    done

    num=0
    printf "plot" >> $archivo

    for FILE in `ls $dir`; do
      if [ $num == 0 ]
        then
        printf  " \"$dir/$FILE\", f$num(x)" >> $archivo
      else printf ", \"$dir/$FILE\", f$num(x)" >> $archivo
      fi

      let num=num+1
    done

    gnuplot ./temporal.gp
    mv fichero.jpeg ./Graficas/$DIR/total_$DIR.jpeg
  fi
done

rm temporal.gp
rm fit.log
