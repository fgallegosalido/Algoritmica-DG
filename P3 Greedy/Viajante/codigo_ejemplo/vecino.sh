#!/bin/bash


for i in `ls -1 ./datosTSP/*.tsp`;
do
   ./a.out $i 1 >> "vecino.dat";
done
