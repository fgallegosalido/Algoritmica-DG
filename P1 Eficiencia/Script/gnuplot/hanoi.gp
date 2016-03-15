set terminal jpeg
set output "fichero.jpeg"

set title "Eficiencia hanoi"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*(2**x)
fit f(x) "datos.dat" via a
plot "datos.dat", f(x)
