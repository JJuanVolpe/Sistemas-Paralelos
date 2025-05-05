#!/bin/bash

# Colores ANSI
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # Sin color

# Compilación
echo "Compilando las versiones..."
gcc -O3 -pthread suma-paralela.c -o suma_paralela
gcc -O3 suma-secuencial.c -o suma_secuencial

# Parámetros
FACTOR=1000000
SIZES=(2 4 8)

echo -e "			============================================"
echo "			  PRUEBA DE RENDIMIENTO - SUMA DE VECTORES "
echo "			============================================"

# Encabezado de tabla
printf "%-20s %-20s %-20s %-10s\n" "Tamaño del vector" "Tiempo Secuencial (s)" "Tiempo Paralelo (s)" "Más rápido"

for size in "${SIZES[@]}"; do
  N=$((size * FACTOR))
  
  # Obtener tiempo secuencial
  T_SEQ=$(./suma_secuencial $N | grep "Tiempo" | awk '{print $NF}')
  
  # Obtener tiempo paralelo
  T_PAR=$(./suma_paralela $N | grep "Tiempo" | awk '{print $NF}')
  
  # Comparar y elegir el más rápido
  if (( $(echo "$T_SEQ < $T_PAR" | bc -l) )); then
    FAST="${GREEN}Secuencial${NC}"
  else
    FAST="${RED}Paralelo${NC}"
  fi

  # Imprimir fila
  printf "%-20d %-20s %-20s %-10b\n" "$N" "$T_SEQ" "$T_PAR" "$FAST"
done
