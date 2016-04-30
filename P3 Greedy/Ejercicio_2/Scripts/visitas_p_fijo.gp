set terminal pngcairo

set output "graficas/visitas_p_fijo.png"
set key font ", 12"
set title "Comparación de visitas (Periodo = 30 días)" font ", 16"
set xlabel "Duración de la reserva (días)" font ", 12"
set ylabel "Visitas" font ", 12"
set style fill transparent solid 0.8
set style line 1 lt 1 lw 2 lc rgb '#409f40'
set style line 2 lt 1 lw 4 lc rgb '#fcbb06'
plot [3:29] "datos/visitas_p_fijo.dat" using 1:3 title 'aleatorio' with filledcurves above y1=0 ls 2, "datos/visitas_p_fijo.dat" using 1:2 title 'greedy' with filledcurves above y1=0 ls 1

set terminal tikz
set output "graficas/visitas_p_fijo.tex"
replot
