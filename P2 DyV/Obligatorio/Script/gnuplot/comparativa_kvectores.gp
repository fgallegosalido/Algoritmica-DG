set terminal pngcairo
set output "comparativa_k.png"

set title "Comparativa mezcla"
set xlabel "Número de vectores"
set ylabel "Tiempo (s)"
set fit quiet
plot "fuerza_bruta.dat", "dyv.dat"
