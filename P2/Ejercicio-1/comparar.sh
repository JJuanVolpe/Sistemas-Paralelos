#!/bin/bash

# Compilar
gcc -O3 suma-secuencial.c -o suma_secuencial -lm
gcc -O3 suma-paralela.c -o suma_paralela -lpthread -lm

# Tamaños y hilos
TAMAÑOS=(2000000 4000000 8000000)
HILOS=(2 4 8)

# Crear archivo de datos
> datos.dat

for N in "${TAMAÑOS[@]}"; do
    echo "# N = $N" >> datos.dat
    for T in "${HILOS[@]}"; do
        TS=$(./suma_secuencial $N | grep "Tiempo" | awk '{print $8}')
        TP=$(./suma_paralela $N $T | grep "Tiempo" | awk '{print $8}')
        SPEEDUP=$(echo "$TS / $TP" | bc -l)
        printf "%d %d %.6f %.6f %.6f\n" $N $T $TS $TP $SPEEDUP >> datos.dat
    done
    echo "" >> datos.dat
done

echo "✅ Pruebas completadas. Resultados en datos.dat"
