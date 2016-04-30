set terminal pngcairo

set output "graficas/visitas_r_fijo.png"
set key font "Helvetica, 14"
set title "Comparación de visitas (Reserva = 5 días)" font "Helvetica, 16"
set xlabel "Tamaño del periodo (días)" font "Helvetica, 12"
set ylabel "Visitas" font "Helvetica, 12"
set style fill transparent solid 0.8
set style line 1 lt 3 lw 2 lc rgb '#409f40'
set style line 2 lt 3 lw 4 lc rgb '#fcbb06'
plot [10:1451] "datos/visitas_r_fijo.dat" using 1:3 title 'aleatorio' with filledcurves above y1=0 ls 2, "datos/visitas_r_fijo.dat" using 1:2 title 'greedy'  with filledcurves above y1=0 ls 1
