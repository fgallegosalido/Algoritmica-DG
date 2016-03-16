set terminal jpeg
set output "fichero.jpeg"

set title "Comparativa optimización Floyd"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
plot "floydO0_ruben.dat"
replot "floydO1_ruben.dat"
replot "floydO2_ruben.dat"
