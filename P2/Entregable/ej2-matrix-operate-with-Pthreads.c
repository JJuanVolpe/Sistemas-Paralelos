#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>

double dwalltime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 0.000001;
}

void printMatrix(double *M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%f\t", M[i * N + j]);
        printf("\n");
    }
    printf("\n");
}

void initMatrix(double *M, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            M[i * N + j] = 1.0;
}

void transpose(double *M, double *MT, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            MT[j * N + i] = M[i * N + j];
}

void blk(int N, int bs, double *A, double *B, double *C) {
    for (int i = 0; i < bs; i++)
        for (int j = 0; j < bs; j++)
            for (int k = 0; k < bs; k++)
                C[i * N + j] += A[i * N + k] * B[j * N + k];  // B está transpuesta
}

typedef struct {
    int thread_id;
    int num_threads;
    int N;
    int bs;
    double *A, *B, *C, *BT, *D, *E;
} thread_data_t;

void *parallel_blkmul(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int tid = data->thread_id;
    int N = data->N;
    int bs = data->bs;
    int num_threads = data->num_threads;
    int blocks_per_thread = (N / bs) * (N / bs) / num_threads;
    int start = tid * blocks_per_thread;
    int end = (tid == num_threads - 1) ? (N / bs) * (N / bs) : start + blocks_per_thread;

    for (int blk_id = start; blk_id < end; blk_id++) {
        int i = (blk_id / (N / bs)) * bs;
        int j = (blk_id % (N / bs)) * bs;
        for (int k = 0; k < N; k += bs) {
            blk(N, bs, &data->A[i * N + k], &data->B[j * N + k], &data->D[i * N + j]);
            blk(N, bs, &data->C[i * N + k], &data->BT[j * N + k], &data->E[i * N + j]);
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int N = (argc > 1) ? atoi(argv[1]) : 1024;
    int bs = (argc > 2) ? atoi(argv[2]) : 64;
    int num_threads = (argc > 3) ? atoi(argv[3]) : 4;

    double *A = (double *)malloc(N * N * sizeof(double));
    double *B = (double *)malloc(N * N * sizeof(double));
    double *BT = (double *)malloc(N * N * sizeof(double));
    double *C = (double *)malloc(N * N * sizeof(double));
    double *D = (double *)calloc(N * N, sizeof(double));
    double *E = (double *)calloc(N * N, sizeof(double));
    double *R = (double *)malloc(N * N * sizeof(double));

    initMatrix(A, N);
    initMatrix(B, N);
    initMatrix(C, N);
    transpose(B, BT, N);

    double start = dwalltime();

    pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
    thread_data_t *thread_data = malloc(sizeof(thread_data_t) * num_threads);

    for (int t = 0; t < num_threads; t++) {
        thread_data[t] = (thread_data_t){t, num_threads, N, bs, A, B, C, BT, D, E};
        pthread_create(&threads[t], NULL, parallel_blkmul, &thread_data[t]);
    }

    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    // Calcular máximos, mínimos y promedios de A y B
    double maxA = A[0], minA = A[0], sumA = 0.0;
    double maxB = B[0], minB = B[0], sumB = 0.0;

    for (int i = 0; i < N * N; i++) {
        if (A[i] > maxA) maxA = A[i];
        if (A[i] < minA) minA = A[i];
        sumA += A[i];
        if (B[i] > maxB) maxB = B[i];
        if (B[i] < minB) minB = B[i];
        sumB += B[i];
    }

    double promA = sumA / (N * N);
    double promB = sumB / (N * N);
    double resultado = (maxA * minA + maxB * minB) / (promA * promB);

    // Calcular R = E + D * resultado
    for (int i = 0; i < N * N; i++)
        R[i] = E[i] + D[i] * resultado;

    double end = dwalltime();
    printf("Tiempo: %f segundos\n", end - start);

    // Liberar memoria
    free(A); free(B); free(BT); free(C); free(D); free(E); free(R);
    free(threads); free(thread_data);

    return 0;
}