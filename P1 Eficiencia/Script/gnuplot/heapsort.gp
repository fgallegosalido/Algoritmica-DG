set terminal jpeg
set output "fichero.jpeg"

set title "Eficiencia heapsort"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
plot "datos.dat"
