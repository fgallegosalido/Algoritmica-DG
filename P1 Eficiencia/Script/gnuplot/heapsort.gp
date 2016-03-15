set terminal pngcairo
set output "fichero.jpeg"

set title "Eficiencia heapsort"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*x*(log(x)/log(2))
fit f(x) "datos.dat" via a
plot "datos.dat", f(x)
