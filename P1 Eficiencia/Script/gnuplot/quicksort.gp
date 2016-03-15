set terminal jpeg
set output "fichero.jpeg"

set title "Eficiencia quicksort"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*x*(log(x)/log(2))
fit f(x) "datos.dat" via a
plot "datos.dat", f(x)
