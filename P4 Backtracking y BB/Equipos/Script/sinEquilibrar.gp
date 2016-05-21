set terminal pngcairo
set output "../Graficas/sinEquilibrar.png"

set title "Eficiencia sin equilibrar número de jugadores"

set xlabel "Total de jugadores"
set ylabel "Tiempo de ejecución (s)"

set fit quiet

f(x)=a*2**x
fit f(x) "../Datos/sinEquilibrar.dat" via a

plot "../Datos/sinEquilibrar.dat" title 'No equilibrados', f(x) title 'f(x)=(3.37262*10^(-6))*2^x' with lines


set terminal tikz
set output "../Graficas/sinEquilibrar.tex"
replot
