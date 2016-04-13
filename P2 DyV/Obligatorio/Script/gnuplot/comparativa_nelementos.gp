set terminal pngcairo
set output "comparativa_n.png"

set title "Comparativa mezcla"
set xlabel "Número de elementos del vector"
set ylabel "Tiempo (s)"
set fit quiet
plot "fuerza_bruta.dat", "dyv.dat"
