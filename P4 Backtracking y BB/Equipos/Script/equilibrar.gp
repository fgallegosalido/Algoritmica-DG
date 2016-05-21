set terminal pngcairo
set output "../Graficas/equilibrar.png"

set title "Eficiencia con equipos equilibrados en número"

set xlabel "Total de jugadores"
set ylabel "Tiempo de ejecución (s)"

set fit quiet

f(x)=a*2**x
fit f(x) "../Datos/equilibrar.dat" via a

plot "../Datos/equilibrar.dat" title 'Equilibrados', f(x) title 'f(x)=(8.73363*10^(-7))*2^' with lines

set terminal tikz
set output "../Graficas/equilibrar.tex"
replot
