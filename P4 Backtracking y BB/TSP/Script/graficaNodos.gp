set terminal pngcairo
set output "../Graficas/graficaNodos.png"

set title "Comparativa de los nodos expandidos"
set xlabel "Fichero en datosTSP"
set ylabel "Nodos expandidos"

set fit quiet
set style fill solid 1.0 border lt -1
set style data histograms

set tics font ", 10"
set style line 1 lt 1 lw 0.5 lc rgb '#409f40'

plot "../DatosGraficas/nodos.dat" using 2:xticlabels(1) title 'Cola algoritmo x0' ls 1


set terminal tikz
set output "../Graficas/graficaNodos.tex"
replot
