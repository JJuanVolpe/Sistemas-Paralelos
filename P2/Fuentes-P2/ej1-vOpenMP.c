#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>  // ← Para OpenMP

// Para calcular tiempo
double dwalltime(){
    double sec;
    struct timeval tv;

    gettimeofday(&tv,NULL);
    sec = tv.tv_sec + tv.tv_usec/1000000.0;
    return sec;
}

int main(int argc, char* argv[]) {
    double *A, *B, *C;
    int i, N;
    int check = 1;
    double timetick;

    // Control de argumentos
    if ((argc != 2) || ((N = atoi(argv[1])) <= 0)) {
        printf("\nUsar: %s n\n  n: Dimension del vector\n", argv[0]);
        exit(1);
    }

    // Alocación de memoria
    A = (double*) malloc(sizeof(double) * N);
    B = (double*) malloc(sizeof(double) * N);
    C = (double*) malloc(sizeof(double) * N);

    // Inicialización paralelizada
    #pragma omp parallel for
    for(i = 0; i < N; i++) {
        A[i] = 1;
        B[i] = 1;
    }

    // Suma paralelizada con cronómetro
    timetick = dwalltime();
    #pragma omp parallel for
    for(i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }
    double time = dwalltime() - timetick;

    printf("Suma de vectores de dimensión %d. Tiempo en segundos %f\n", N, time);

    // Verificación con reducción lógica
    check = 1;
    #pragma omp parallel for reduction(&&:check)
    for(i = 0; i < N; i++) {
        check = check && (C[i] == 2);
    }

    if (check) {
        printf("Suma de vectores resultado correcto\n");
    } else {
        printf("Suma de vectores resultado erroneo\n");
    }

    free(A);
    free(B);
    free(C);
    return 0;
}
