set terminal pngcairo
set output "../Graficas/graficaNodos.png"

set title "Comparativa de los nodos expandidos según algoritmo de poda"
set xlabel "Fichero en datosTSP"
set ylabel "Nodos expandidos"

set fit quiet
set style fill solid 1.0 border lt -1
set style data histograms

set tics font ", 10"
set style line 1 lt 1 lw 0.5 lc rgb '#409f40'
set style line 2 lt 1 lw 0.5 lc rgb '#fcbb06'
set style line 3 lt 1 lw 0.5 lc rgb '#f44c04'

plot "../DatosGraficas/nodos.dat" using 2:xticlabels(1) title 'Nodos algoritmo x0' ls 1,
"../DatosGraficas/nodos.dat" using 3:xticlabels(1) title 'Nodos algoritmo x1' ls 2,
"../DatosGraficas/nodos.dat" using 4:xticlabels(1) title 'Nodos algoritmo x2' ls 3


set terminal tikz
set output "../Graficas/graficaNodos.tex"
replot
