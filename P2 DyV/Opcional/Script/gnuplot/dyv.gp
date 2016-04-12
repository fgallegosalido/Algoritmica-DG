set terminal pngcairo
set output "grafica.png"

set title "Divide y vencerás"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*x*x + b*x + c
fit f(x) "datos.dat" via a, b, c
plot "datos.dat" title 'datos', f(x) title 'f(n) = an^2 + bn + c'
