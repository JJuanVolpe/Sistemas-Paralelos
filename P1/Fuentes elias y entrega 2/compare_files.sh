#!/bin/bash

# Validación de cantidad mínima de archivos
if [ "$#" -lt 2 ]; then
  echo "Uso: $0 archivo1.c archivo2.c [archivo3.c ... archivoN.c]"
  exit 1
fi

ARCHIVOS=("$@")
TOTAL=${#ARCHIVOS[@]}

echo "🔍 Comparando $TOTAL archivos..."

# Función auxiliar: compara dos archivos línea por línea
comparar_archivos() {
  local file1="$1"
  local file2="$2"
  echo
  echo "== Comparando: $file1 ⬄ $file2 =="

  local max_lines
  local lines1 lines2
  lines1=$(wc -l < "$file1")
  lines2=$(wc -l < "$file2")
  max_lines=$(( lines1 > lines2 ? lines1 : lines2 ))

  local i
  local line1 line2

  local diferencias=0

  for (( i=1; i<=max_lines; i++ )); do
    line1=$(sed -n "${i}p" "$file1")
    line2=$(sed -n "${i}p" "$file2")

    if [ "$line1" != "$line2" ]; then
      diferencias=1
      if [ -n "$line1" ]; then
        echo "🔽 Sólo en $file1 (línea $i): $line1"
      fi
      if [ -n "$line2" ]; then
        echo "🔼 Sólo en $file2 (línea $i): $line2"
      fi
    fi
  done

  if [ "$diferencias" -eq 0 ]; then
    echo "✅ Sin diferencias."
  fi
}

# Comparaciones por pares
for ((i=0; i<TOTAL-1; i++)); do
  for ((j=i+1; j<TOTAL; j++)); do
    comparar_archivos "${ARCHIVOS[i]}" "${ARCHIVOS[j]}"
  done
done
