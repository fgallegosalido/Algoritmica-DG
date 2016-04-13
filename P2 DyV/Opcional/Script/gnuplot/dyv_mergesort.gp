set terminal pngcairo
set output "grafica.png"

set title "Divide y vencerás con mergesort"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*x*(log(x)/log(2))
fit f(x) "datos.dat" via a
plot "datos.dat" title 'datos', f(x) title 'f(n) = a*n*log_2(x)'
