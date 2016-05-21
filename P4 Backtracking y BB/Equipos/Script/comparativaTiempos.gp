set terminal pngcairo
set output "../Graficas/tiempos.png"

set title "Eficiencia división en equipos"

set xlabel "Total de jugadores"
set ylabel "Tiempo de ejecución (s)"

set fit quiet

f(x)=a*2**x
fit f(x) "../Datos/sinEquilibrar.dat" via a

g(x)=b*2**x
fit g(x) "../Datos/equilibrar.dat" via b

plot "../Datos/sinEquilibrar.dat" title 'Sin equilibrar', "../Datos/equilibrar.dat" title 'Equilibrados', f(x), g(x)

set terminal tikz
set output "../Graficas/tiempos.tex"
replot
