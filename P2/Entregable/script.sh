#!/bin/bash

# Parámetros fijos
N=512
EXEC=./ej2-proof # Reemplazá por el nombre de tu ejecutable
SALIDA="resultados.csv"

# Limpio archivo anterior
echo "bs,num_threads,time" > $SALIDA

# Recorro combinaciones
for bs in 8 16 32 64 128; do
  for hilos in 1 2 4 8; do
    echo "Ejecutando: N=$N bs=$bs hilos=$hilos"
    tiempo=$($EXEC $N $bs $hilos | grep "Tiempo" | awk '{print $2}')
    echo "$bs,$hilos,$tiempo" >> $SALIDA
  done
done
