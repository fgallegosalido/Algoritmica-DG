set terminal pngcairo
set output "grafica_d.png"

set title "Mezcla por divide y vencerás"
set xlabel "Elementos por vector"
set ylabel "Vectores"
set zlabel "T(s)"

set hidden3d
set dgrid3d qnorm 2
splot "dyv.dat" with lines
