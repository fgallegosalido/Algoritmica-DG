set terminal pngcairo

set output "graficas/media.png"
set key font ", 12"
set title "Comparación de visitas (media)" font ", 16"
set style fill solid 1.0 border lt -1
set style data histograms
set xlabel "Tamaño del periodo (meses)" font ", 12"
set ylabel "Visitas" font ", 12"
set tics font ", 10"
set style line 1 lt 1 lw 0.5 lc rgb '#409f40'
set style line 2 lt 1 lw 0.5 lc rgb '#fcbb06'
set style line 2 lt 1 lw 0.5 lc rgb '#f44c04'
plot "datos/media.dat" using 2:xticlabels(1) title 'greedy' ls 1, "datos/media.dat" using 3:xticlabels(1) title 'aleatorio' ls 2

set terminal tikz
set output "graficas/media.tex"
replot
