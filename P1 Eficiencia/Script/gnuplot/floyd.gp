set terminal jpeg
set output "fichero.jpeg"

set title "Eficiencia floyd"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
set fit quiet
f(x) = a*x*x*x+b*x*x+c*x+d
fit f(x) "datos.dat" via a, b, c, d
plot "datos.dat", f(x)
