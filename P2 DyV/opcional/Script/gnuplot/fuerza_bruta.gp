set terminal pngcairo
set output "grafica.jpeg"

set title "Fuerza bruta"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*x*x + b*x + c
fit f(x) "datos.dat" via a, b, c
plot "datos.dat", f(x)
