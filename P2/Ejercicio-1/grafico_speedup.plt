set title "Speedup de Suma Paralela con Pthreads"
set xlabel "Cantidad de Hilos"
set ylabel "Speedup"
set grid
set key outside
set style data linespoints

plot for [i=1:3] \
    'datos.dat' index i using 2:5 title sprintf("N = %.0f", word("2000000 4000000 8000000", i)) with linespoints lw 2 pt i
