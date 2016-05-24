set terminal pngcairo
set output "../Graficas/graficaTiempos0.png"

set title "Comparativa del tiempo según tipo de poda"
set xlabel "Fichero en datosTSP"
set ylabel "Tiempo (s)"

set fit quiet
set style fill solid 1.0 border lt -1
set style data histograms
set tics font ", 10"

plot "../DatosGraficas/tiempos.dat" using 2:xticlabels(1) title 'Tiempos algoritmo x0'
set terminal tikz
set output "../Graficas/graficaTiempos0.tex"
replot

set output "../Graficas/graficaTiempos1.png"
plot "../DatosGraficas/tiempos.dat" using 3:xticlabels(1) title 'Tiemposs algoritmo x1'
set terminal tikz
set output "../Graficas/graficaTiempos1.tex"
replot

set output "../Graficas/graficaTiempos2.png"
plot "../DatosGraficas/tiempos.dat" using 4:xticlabels(1) title 'Tiempos algoritmo x2'
set terminal tikz
set output "../Graficas/graficaTiempos2.tex"
replot


set style line 1 lt 1 lw 0.5 lc rgb '#409f40'
set style line 2 lt 1 lw 0.5 lc rgb '#fcbb06'
set style line 3 lt 1 lw 0.5 lc rgb '#f44c04'

set output "../Graficas/graficaTiempos.png"
plot "../DatosGraficas/tiempos.dat" using 2:xticlabels(1) title 'Tiempo algoritmo x0' ls 1,
"../DatosGraficas/tiempos.dat" using 3:xticlabels(1) title 'Tiempo algoritmo x1' ls 2,
"../DatosGraficas/tiempos.dat" using 4:xticlabels(1) title 'Tiempo algoritmo x2' ls 3

set terminal tikz
set output "../Graficas/graficaTiempos.tex"
replot
