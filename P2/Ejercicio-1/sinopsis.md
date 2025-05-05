## ❌ Regiones que no pueden ejecutarse en paralelo
 - La inicialización de N desde los argumentos
 - La llamada a malloc (aunque es rápida)
 - El cálculo de tiempo (dwalltime()) debe mantenerse en la sección secuencial


## ✅ La arquitectura es homogénea: asumimos que estamos en un sistema con CPUs similares (multi-core tradicional).

**Por eso, se puede distribuir con partición por bloques:**

Cada hilo procesa un segmento de N/T elementos.

# 📌 Notas:
La división del trabajo es pareja (regular).

- El chunk garantiza que cada hilo tiene aproximadamente N / T elementos.

- El último hilo cubre cualquier remanente (end = N si es el último).

🧾 Resumen de ejecución + análisis gráfico
📁 Archivos necesarios:
suma-secuencial.c → Versión secuencial

suma-paralela.c → Versión con Pthreads

comparar.sh → Script de compilación y prueba

datos.dat → Archivo de salida con los resultados

grafico_speedup.plt → Script de Gnuplot para graficar speedup

grafico_tiempos.plt → Script de Gnuplot para graficar tiempos absolutos

