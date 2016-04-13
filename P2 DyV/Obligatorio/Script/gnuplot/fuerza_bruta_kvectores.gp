set terminal pngcairo
set output "grafica_f.png"

set title "Mezcla por fuerza bruta"
set xlabel "Número de vectores"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*x*x
fit f(x) "fuerza_bruta.dat" via a
plot "fuerza_bruta.dat", f(x)
