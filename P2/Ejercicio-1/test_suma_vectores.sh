#!/bin/bash

# Compilación
echo "Compilando las versiones..."
gcc -O3 -pthread suma-paralela.c -o suma_paralela
gcc -O3 suma-secuencial.c -o suma_secuencial

# Parámetros
FACTOR=1000000
SIZES=(2 4 8)

echo -e "\n==========================================="
echo " PRUEBA DE RENDIMIENTO - SUMA DE VECTORES "
echo "===========================================\n"

for size in "${SIZES[@]}"; do
  N=$((size * FACTOR))
  echo "Tamaño del vector: $N elementos"

  echo -n "➤ Versión secuencial: "
  ./suma_secuencial $N | grep "Tiempo"

  echo -n "➤ Versión paralela (Pthreads): "
  ./suma_paralela $N | grep "Tiempo"

  echo "-------------------------------------------"
done
""" Prueba día 19/4/2025:
===========================================
 PRUEBA DE RENDIMIENTO - SUMA DE VECTORES 
===========================================\n
Tamaño del vector: 2000000 elementos
➤ Versión secuencial: Suma de vectores de dimensión 2000000. Tiempo en segundos 0.007531
➤ Versión paralela (Pthreads): Suma de vectores de dimensión 2000000. Tiempo en segundos 0.012916
-------------------------------------------
Tamaño del vector: 4000000 elementos
➤ Versión secuencial: Suma de vectores de dimensión 4000000. Tiempo en segundos 0.014929
➤ Versión paralela (Pthreads): Suma de vectores de dimensión 4000000. Tiempo en segundos 0.025226
-------------------------------------------
Tamaño del vector: 8000000 elementos
➤ Versión secuencial: Suma de vectores de dimensión 8000000. Tiempo en segundos 0.029256
➤ Versión paralela (Pthreads): Suma de vectores de dimensión 8000000. Tiempo en segundos 0.050911
"""