set terminal pngcairo
set output "grafica_d.png"

set title "Mezcla por divide y vencerás"
set xlabel "Número de elementos por vector"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*x*(log(x)/log(2))
fit f(x) "dyv.dat" via a
plot "dyv.dat", f(x)
