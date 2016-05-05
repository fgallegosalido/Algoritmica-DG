#!/bin/bash


for i in `ls -1 datosTSP/*.tsp`;
do
   var=`echo $i | cut -d'.' -f1`
   # echo "./$var.tsp"
   echo "$var.opt.dat"
   ./tsp $i "$var.opt.tour" > "$var.opt.dat"
   ./distance $var.opt.dat >> opt.dat
done
