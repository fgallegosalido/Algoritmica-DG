#!/bin/bash
MIN_P=10
MAX_P=1461
MIN_R=3


tiempo.dat
printf "" > datos/tiempo.dat
periodo=$MIN_P
while [ $periodo -lt $MAX_P ]; do
  reserva=$MIN_R
  while [ $reserva -lt $periodo ]; do
    printf $periodo >> datos/tiempo.dat
    printf " " >> datos/tiempo.dat
    printf $reserva >> datos/tiempo.dat
    printf " " >> datos/tiempo.dat
    ./bin/minimizar_visitas $periodo $reserva | cut -d " " -f 2 >> datos/tiempo.dat
    let reserva=reserva+1
  done
  let periodo=periodo+1
done
echo "Terminado tiempo.dat"


#visitas_r_fijo.dat
printf "" > datos/visitas_r_fijo.dat
reserva=5
periodo=$MIN_P
while [ $periodo -lt $MAX_P ]; do
  printf $periodo >> datos/visitas_r_fijo.dat
  printf " " >> datos/visitas_r_fijo.dat
  ./bin/minimizar_visitas $periodo $reserva | cut -d " " -f 1 | head -c-1 >> datos/visitas_r_fijo.dat
  printf " " >> datos/visitas_r_fijo.dat
  ./bin/visitas_aleatorias $periodo $reserva | cut -d " " -f 1 | head -c-1 >> datos/visitas_r_fijo.dat
  printf "\n" >> datos/visitas_r_fijo.dat
  let periodo=periodo+30
done
echo "Terminado visitas_r_fijo.dat"


#visitas_p_fijo.dat
printf "" > datos/visitas_p_fijo.dat
periodo=30
reserva=$MIN_R
while [ $reserva -lt $periodo ]; do
  printf $reserva >> datos/visitas_p_fijo.dat
  printf " " >> datos/visitas_p_fijo.dat
  ./bin/minimizar_visitas $periodo $reserva | cut -d " " -f 1 | head -c-1 >> datos/visitas_p_fijo.dat
  printf " " >> datos/visitas_p_fijo.dat
  ./bin/visitas_aleatorias $periodo $reserva | cut -d " " -f 1 | head -c-1 >> datos/visitas_p_fijo.dat
  printf "\n" >> datos/visitas_p_fijo.dat
  let reserva=reserva+1
done
echo "Terminado visitas_p_fijo.dat"


#media.dat
printf "" > datos/media.dat
periodo=30
while [ $periodo -lt $MAX_P ]; do
  i=0
  m1=0
  m2=0
  while [ $i -lt 2000 ]; do
    v=`./bin/minimizar_visitas $periodo | cut -d " " -f 1  | head -c-1`
    let m1=m1+v
    v=`./bin/visitas_aleatorias $periodo | cut -d " " -f 1  | head -c-1`
    let m2=m2+v
    let i=i+1
  done
  let m1=m1/i
  let m2=m2/i
  let p=$periodo/30
  printf $p >> datos/media.dat
  printf " " >> datos/media.dat
  printf $m1 >> datos/media.dat
  printf " " >> datos/media.dat
  printf $m2 >> datos/media.dat
  printf "\n" >> datos/media.dat
  let periodo=periodo+60
done
echo "Terminado media.dat"
