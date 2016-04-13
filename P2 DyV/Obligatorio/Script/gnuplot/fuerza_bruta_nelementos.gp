set terminal pngcairo
set output "grafica_f.png"

set title "Mezcla por fuerza bruta"
set xlabel "Número de elementos por vector"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*x
fit f(x) "fuerza_bruta_nelementos.dat" via a
plot "fuerza_bruta_nelementos.dat", f(x)
