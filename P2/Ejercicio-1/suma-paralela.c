#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define NUM_THREADS 4  // Cantidad de hilos (cores disponibles)

double *A, *B, *C;
int N;
int check = 1; // Resultado final de verificación
int check_thread[NUM_THREADS]; // Resultados parciales por hilo

// Para calcular tiempo
double dwalltime(){
    double sec;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    sec = tv.tv_sec + tv.tv_usec/1000000.0;
    return sec;
}

// Estructura para pasar datos a los hilos
typedef struct {
    int tid;
    int start;
    int end;
} thread_data_t;

// Función que ejecutan los hilos
void* thread_func(void* arg) {
    thread_data_t* data = (thread_data_t*) arg;
    int tid = data->tid;
    int i;

    // Inicialización de A y B
    for (i = data->start; i < data->end; i++) {
        A[i] = 1;
        B[i] = 1;
    }

    // Suma de vectores
    for (i = data->start; i < data->end; i++) {
        C[i] = A[i] + B[i];
    }

    // Verificación parcial
    check_thread[tid] = 1;
    for (i = data->start; i < data->end; i++) {
        if (C[i] != 2) {
            check_thread[tid] = 0;
            break;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int i;

    double timetick;

    if ((argc != 2) || ((N = atoi(argv[1])) <= 0)) {
        printf("\nUsar: %s n\n  n: Dimension del vector\n", argv[0]);
        exit(1);
    }

    A = (double*) malloc(sizeof(double) * N);
    B = (double*) malloc(sizeof(double) * N);
    C = (double*) malloc(sizeof(double) * N);

    int chunk = N / NUM_THREADS;

    timetick = dwalltime();

    // Crear hilos
    for (i = 0; i < NUM_THREADS; i++) {
        thread_data[i].tid = i;
        thread_data[i].start = i * chunk;
        thread_data[i].end = (i == NUM_THREADS - 1) ? N : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, thread_func, (void*)&thread_data[i]);
    }

    // Esperar a los hilos
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double time = dwalltime() - timetick;
    printf("Suma de vectores de dimensión %d. Tiempo en segundos %f\n", N, time);

    // Reducción del resultado final
    for (i = 0; i < NUM_THREADS; i++) {
        check = check && check_thread[i];
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
