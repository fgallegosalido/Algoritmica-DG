set terminal pngcairo
set output "../Graficas/comparativa.png"

set title "Comparación entre equipos equilibrados o no"
set style fill solid 1.0 border lt -1
set style data histograms
set xlabel "Total de jugadores" font ", 12"
set ylabel "Diferencia de nivel entre los equipos" font ", 12"

set tics font ", 10"
set style line 1 lt 1 lw 0.5 lc rgb '#409f40'
set style line 2 lt 1 lw 0.5 lc rgb '#fcbb06'
plot "../Datos/distancias.dat" using 2:xticlabels(1) title 'Sin equillibrar' ls 1, "../Datos/distancias.dat" using 3:xticlabels(1) title 'Equilibrados' ls 2

set terminal tikz
set output "../Graficas/comparativa.tex"
replot
