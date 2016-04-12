set terminal pngcairo
set output "comparativa.png"

set title "Comparativa mezcla"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
set fit quiet
plot "../../Datos/dyv_bruno.dat", "../../Datos/fuerza_bruta_bruno.dat"
