set terminal pngcairo
set output "comparativa.png"

set title "Comparativa mezcla"
set xlabel "Tamaño del vector"
set ylabel "Tiempo (s)"
set fit quiet
plot "../../Datos/dyv_bruno.dat" title 'dyv', "../../Datos/fuerza_bruta_bruno.dat" title 'fuerza bruta', "../../Datos/dyv_mergesort_bruno.dat" title 'dyv mergesort'
