import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

# Leer los resultados
df = pd.read_csv("resultados.csv")

# -----------------------
# PALETA DE COLORES
# -----------------------
sns.set_palette("tab10")  # colores más contrastantes para humanos
markers = ['o', 's', '^', 'D', 'X', '*', 'v', '<']

# -----------------------
# GRÁFICO 1: BÁSICO
# -----------------------
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="bs", y="time", hue="num_threads", marker="o")
plt.title("Tiempo vs Tamaño de bloque para distintos hilos")
plt.xlabel("Tamaño de bloque (bs)")
plt.ylabel("Tiempo (segundos)")
plt.legend(title="Hilos")
plt.grid(True)
plt.tight_layout()
plt.savefig("rendimiento.png")
os.system("xdg-open rendimiento.png")

# -----------------------
# GRÁFICO 1B: ESCALA LOG
# -----------------------
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="bs", y="time", hue="num_threads", marker="o")
plt.xscale("log")
plt.yscale("log")
plt.title("Tiempo vs Tamaño de bloque (escala log)")
plt.xlabel("Tamaño de bloque (bs)")
plt.ylabel("Tiempo (segundos)")
plt.legend(title="Hilos")
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.tight_layout()
plt.savefig("rendimiento_log.png")
os.system("xdg-open rendimiento_log.png")

# -----------------------
# GRÁFICO 2: DIFERENCIA POR bs
# -----------------------
# Calcular diferencia porcentual entre hilos para cada bs
df_diff_bs = df.copy()
df_diff_bs['time_pct'] = df_diff_bs.groupby('bs')['time'].transform(lambda x: 100 * (x - x.min()) / x.min())

plt.figure(figsize=(10, 6))
sns.lineplot(data=df_diff_bs, x="bs", y="time_pct", hue="num_threads", marker="o")
plt.title("Diferencia porcentual por Tamaño de bloque")
plt.xlabel("Tamaño de bloque (bs)")
plt.ylabel("Diferencia (%) respecto al mejor tiempo por bs")
plt.grid(True)
plt.tight_layout()
plt.savefig("diferencia_bs.png")
os.system("xdg-open diferencia_bs.png")

# -----------------------
# GRÁFICO 3: DIFERENCIA POR num_threads
# -----------------------
df_diff_threads = df.copy()
df_diff_threads['time_pct'] = df_diff_threads.groupby('num_threads')['time'].transform(lambda x: 100 * (x - x.min()) / x.min())

plt.figure(figsize=(10, 6))
sns.lineplot(data=df_diff_threads, x="num_threads", y="time_pct", hue="bs", marker="o")
plt.title("Diferencia porcentual por cantidad de hilos")
plt.xlabel("Cantidad de hilos")
plt.ylabel("Diferencia (%) respecto al mejor tiempo por hilos")
plt.grid(True)
plt.tight_layout()
plt.savefig("diferencia_hilos.png")
os.system("xdg-open diferencia_hilos.png")
