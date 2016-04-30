set terminal pngcairo
set output "graficas/tiempo.png"

set key font "Helvetica, 14"
set title "Eficiencia del algoritmo" font "Helvetica, 16"
unset key
set xlabel "Tamaño del periodo (días)"  font "Helvetica, 12" offset graph 0,0,-0.3
set ylabel "Duración de la reserva (días)"  font "Helvetica, 12" offset graph 0,0,-0.435
set zlabel "Tiempo (s)" font "Helvetica, 12" offset graph 0,-0.2,0.6
set tics font "Helvetica, 10"
set autoscale zfixmax
set hidden3d
set dgrid3d qnorm 2
set palette defined (0 '#409f40', 1 '#fcbb0', 2 '#f49b04', 3 '#f44c04')
set style line 1 lt 4 lw 1 lc 'gray'
set pm3d at s hidden3d 1
set view 57, 218
splot "datos/tiempo.dat" with lines
