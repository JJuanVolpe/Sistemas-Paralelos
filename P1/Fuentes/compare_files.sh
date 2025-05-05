#!/bin/bash

# Verifica que se hayan pasado exactamente 3 archivos como parámetros
if [ "$#" -ne 3 ]; then
  echo "Uso: $0 archivo1.c archivo2.c archivo3.c"
  exit 1
fi

A1="$1"
A2="$2"
A3="$3"

echo "== Comparando $A1 y $A2 =="
diff_output=$(diff "$A1" "$A2")
if [ -n "$diff_output" ]; then
  echo "❗ Diferencias encontradas entre $A1 y $A2:"
  echo "$diff_output"
else
  echo "✅ Sin diferencias entre $A1 y $A2."
fi

echo
echo "== Comparando $A2 y $A3 =="
diff_output=$(diff "$A2" "$A3")
if [ -n "$diff_output" ]; then
  echo "❗ Diferencias encontradas entre $A2 y $A3:"
  echo "$diff_output"
else
  echo "✅ Sin diferencias entre $A2 y $A3."
fi

echo
echo "== Comparando $A1 y $A3 =="
diff_output=$(diff "$A1" "$A3")
if [ -n "$diff_output" ]; then
  echo "❗ Diferencias encontradas entre $A1 y $A3:"
  echo "$diff_output"
else
  echo "✅ Sin diferencias entre $A1 y $A3."
fi

echo
echo "== Comparación de tres archivos con diff3 (suponiendo que $A2 es la base común) =="
diff3_output=$(diff3 "$A1" "$A2" "$A3")
if [ -n "$diff3_output" ]; then
  echo "❗ Conflictos detectados por diff3:"
  echo "$diff3_output"
  echo
  echo "📌 Comentario: Las secciones marcadas con '====' son conflictos. Los que aparecen sólo en 2 de 3 archivos muestran en qué archivo falta el contenido."
else
  echo "✅ Los tres archivos son idénticos o no hay conflictos relevantes detectados."
fi
