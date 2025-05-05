4. Dada la ecuación cuadrática: x
2 − 4.0000000 x + 3.9999999 = 0, sus raíces son r1 = 2.000316228 y r2 =
1.999683772 (empleando 10 dígitos para la parte decimal).
a. El algoritmo quadratic1.c computa las raíces de esta ecuación empleando los tipos de datos
float y double. Compile y ejecute el código. ¿Qué diferencia nota en el resultado?
Soluciones Float: 2.00000       2.00000
Soluciones Double: 2.00032      1.99968

Redondea o trunca el número con menor precisión el tipo float
Cada función calcula los discriminantes de dicha ecuación para obtener las raíces.
Con float: Calcula las raíces de la ecuación utilizando float y las muestra con precisión de 5 decimales.
Con double: Calcula las raíces de la ecuación utilizando double y las muestra con mayor precisión. 

En servidor:
Soluciones Float: 2.00000       2.00000
Soluciones Double: 2.00032      1.99968
Batch job -> 131115

b. El algoritmo quadratic2.c computa las raíces de esta ecuación, pero en forma repetida. Compile
y ejecute el código variando la constante TIMES. ¿Qué diferencia nota en la ejecución?

### TIMES=20 =>
Tiempo requerido solucion Double: 5.971957
Tiempo requerido solucion Float: 6.543199
En servidor:
Tiempo requerido solucion Double: 9.237869
Tiempo requerido solucion Float: 9.190847
Batch job -> 131118

### TIMES=100 =>
Tiempo requerido solucion Double: 29.972080
Tiempo requerido solucion Float: 32.746975
En servidor:
Tiempo requerido solucion Double: 45.136906
Tiempo requerido solucion Float: 45.636677
Batch job -> 131119

### TIMES=200 =>
Tiempo requerido solucion Double: 60.127173
Tiempo requerido solucion Float: 65.640004
En servidor:
Tiempo requerido solucion Double: 90.243492
Tiempo requerido solucion Float: 93.551877
Batch job -> 131121

### TIMES=250 =>
Tiempo requerido solucion Double: 75.275802
Tiempo requerido solucion Float: 82.089031
En servidor:
Tiempo requerido solucion Double: 112.791632
Tiempo requerido solucion Float: 117.053211
Batch job -> 131122
### Conclusión:

Al variar la constante `TIMES`, se observa que el tiempo de ejecución aumenta a medida que se repiten más cálculos. Aunque la diferencia de tiempo entre las soluciones con `float` y `double` es pequeña al principio, esta se vuelve más notable con el incremento de `TIMES`.

- **Con `double`**: A medida que aumenta el número de repeticiones, el tiempo requerido crece de manera relativamente más pronunciada, debido al mayor costo computacional de las operaciones de mayor precisión.
  
- **Con `float`**: Aunque el tiempo también aumenta con `TIMES`, el impacto es menor que con `double`, ya que las operaciones de `float` son más rápidas pero con menor precisión.


c. El algoritmo quadratic3.c computa las raíces de esta ecuación, pero en forma repetida. Compile
y ejecute el código variando la constante TIMES. ¿Qué diferencia nota en la ejecución? ¿Qué
diferencias puede observar en el código con respecto a quadratic2.c?

### TIMES=20 =>
Tiempo requerido solucion Double: 5.991154
Tiempo requerido solucion Float: 4.295285

En servidor:
Tiempo requerido solucion Double: 9.024581
Tiempo requerido solucion Float: 13.825689
Batch job -> 131124
### TIMES=100 =>
Tiempo requerido solucion Double: 30.004305
Tiempo requerido solucion Float: 21.535471

En servidor:
Tiempo requerido solucion Double: 45.109969
Tiempo requerido solucion Float: 69.131914
Batch job -> 131123
### times=200 =>
Tiempo requerido solucion Double: 60.449517
Tiempo requerido solucion Float: 43.009751

En servidor:
Tiempo requerido solucion Double: 90.201206
Tiempo requerido solucion Float: 138.261703
Batch job -> 131125
### TIMES=250 =>
Tiempo requerido solucion Double: 75.365255
Tiempo requerido solucion Float: 53.930357

En servidor [Partición Blade]:
Tiempo requerido solucion Double: 112.836745
Tiempo requerido solucion Float: 172.881651
Batch job -> 131126

En servidor [Partición XeonPHI]:
Tiempo requerido solucion Double/Float > 13.30MIN (aprox 800 seg.)
Batch job -> 131127

En servidor [Partición GPUS]:
Tiempo requerido solucion Double: 126.447740
Tiempo requerido solucion Float: 79.480969 
Batch job -> 131128

-
Nota: agregue el flag -lm al momento de compilar. Pruebe con el nivel de optimización que mejor resultado le haya dado en el ejercicio anterior.

