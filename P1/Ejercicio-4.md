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

b. El algoritmo quadratic2.c computa las raíces de esta ecuación, pero en forma repetida. Compile
y ejecute el código variando la constante TIMES. ¿Qué diferencia nota en la ejecución?

### TIMES=20 =>
Tiempo requerido solucion Double: 5.971957
Tiempo requerido solucion Float: 6.543199
### TIMES=100 =>
Tiempo requerido solucion Double: 29.972080
Tiempo requerido solucion Float: 32.746975

### TIMES=200 =>
Tiempo requerido solucion Double: 60.127173
Tiempo requerido solucion Float: 65.640004

### TIMES=250 =>
Tiempo requerido solucion Double: 75.275802
Tiempo requerido solucion Float: 82.089031
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
### TIMES=100 =>
Tiempo requerido solucion Double: 30.004305
Tiempo requerido solucion Float: 21.535471
### times=200 =>
Tiempo requerido solucion Double: 60.449517
Tiempo requerido solucion Float: 43.009751
### TIMES=250 =>
Tiempo requerido solucion Double: 75.365255
Tiempo requerido solucion Float: 53.930357


-
Nota: agregue el flag -lm al momento de compilar. Pruebe con el nivel de optimización que mejor resultado le haya dado en el ejercicio anterior.

