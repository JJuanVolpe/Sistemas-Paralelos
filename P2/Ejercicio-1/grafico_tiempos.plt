set title "Tiempo de ejecución - Secuencial vs Paralelo"
set xlabel "Cantidad de Hilos"
set ylabel "Tiempo (segundos)"
set grid
set key outside
set style data linespoints

plot for [i=1:3] \
    'datos.dat' index i using 2:3 title sprintf("Sec. N=%.0f", word("2000000 4000000 8000000", i)) lt 1 pt 1 lw 2, \
    'datos.dat' index i using 2:4 title sprintf("Par. N=%.0f", word("2000000 4000000 8000000", i)) lt 2 pt 2 lw 2
