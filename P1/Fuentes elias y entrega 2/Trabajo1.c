#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // duda con el 1_3

void initvalmat(double *bt, int n, double *b); 
void blkmul(int N, int bs, double *M1, double *M2, double *Res);
void blk(int N, int bs, double *M1blk, double *M2blk, double *Resblk);
void sumaM(int N, int bs, double *D, double *E, double *R, double resultado);

double dwalltime(){
        double sec;
        struct timeval tv;

        gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;
        return sec;
}

int main(int argc, char *argv[]) {
    double *A,*B,*C,*R,*BT,*D,*E,*Dblk,*Eblk,*Rblk,*Ablk,*Bblk,*Cblk,*BTblk, aux;
    int N,i,j,k,i2,j2,k2,bs;
    int check=1;
    double timetick,timeend,aMin=__DBL_MAX__,bMin=__DBL_MAX__,aMax=-__DBL_MAX__,bMax=-__DBL_MAX__,aProm,bProm,aSuma=0,bSuma=0,resultado,Aux;


     //Controla los argumentos al programa
  if ( (argc != 3) || ((N = atoi(argv[1])) <= 0) || ((bs = atoi(argv[2])) <= 0) || ((N % bs) != 0))
  {
    printf("\nError en los parametros. Usage: ./%s N BS (N debe ser multiplo de BS)\n", argv[0]);
    exit(1);
  }
  printf("Bloque: [%d]\n",bs);
    //Aloca memoria para las matrices
    A=(double*)malloc(sizeof(double)*N*N);
    B=(double*)malloc(sizeof(double)*N*N);
    C=(double*)malloc(sizeof(double)*N*N);
    R=(double*)malloc(sizeof(double)*N*N);
    BT=(double*)malloc(sizeof(double)*N*N);
    D=(double*)malloc(sizeof(double)*N*N);
    E=(double*)malloc(sizeof(double)*N*N);

    //Inicializar matrices
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i * N + j] = i + 1;
            R[i*N+j]=0;
            D[i*N+j]=0;
            E[i*N+j]=0;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            B[j+i*N] = 2.0 * (i + 1);
        }
    }
    // Modificamos una posición para tener un valor distinto
    B[1] = 5.0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i * N + j] = (i + 1) * (j + 1);
        }
    }

    timetick = dwalltime();
    initvalmat(BT,N,B);
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){ 
            aSuma+=A[i*N+j];  
            if(A[i*N+j]<aMin){
                aMin=A[i*N+j];
            }
            if(A[i*N+j]>aMax){
                aMax=A[i*N+j];
            }      
            bSuma+=B[j+i*N];
            if(B[j+i*N]<bMin){
                bMin=B[j+i*N];
            }
            if(B[j+i*N]>bMax){
                bMax=B[j+i*N];
            } 
        }
    }
      aProm=aSuma/(N*N);
      bProm=bSuma/(N*N);
      resultado=(aMax*bMax - aMin*bMin)/(aProm*bProm);

    blkmul(N, bs, A, B, D);
    blkmul(N, bs, C, BT, E);
    sumaM(N, bs, D, E, R, resultado);
    
    printf("Multiplicacion de matrices de %dx%d. Tiempo en segundos %f\n",N,N, (dwalltime() - timetick));

   // Liberar la memoria
    free(A);
    free(B);
    free(C);
    free(R);
    free(D);
    free(BT);
    free(E);
    return 0;
}

void initvalmat(double *bt, int n, double *b)
{
  int i, j;
	for (i = 0; i < n; i++)
	{
	  for (j = 0; j < n; j++)
		{
		  bt[j*n + i] = b[i*n+j];
		}
	}
}

void blkmul(int N, int bs, double *M1, double *M2, double *Res) {
  for (int i = 0; i < N; i += bs) {
      for (int j = 0; j < N; j += bs) {
          for (int k = 0; k < N; k += bs) {
              blk(N, bs, &M1[i*N+k], &M2[j*N+k], &Res[i*N+j]);
          }
      }
  }
}
void blk(int N, int bs, double *M1blk, double *M2blk, double *Resblk) {
  for (int i2 = 0; i2 < bs; i2++) {
      for (int j2 = 0; j2 < bs; j2++) {
          double aux = 0;
          for (int k2 = 0; k2 < bs; k2++) {
              aux += M1blk[i2*N + k2] * M2blk[j2*N + k2];
          }
          Resblk[i2*N + j2] += aux;
      }
  }
}
void sumaM(int N, int bs, double *D, double *E, double *R, double resultado) {
  for (int i = 0; i < N; i += bs) {
      for (int j = 0; j < N; j += bs) {
          double *Eblk = &E[i*N+j];
          double *Rblk = &R[i*N+j];
          double *Dblk = &D[i*N+j];

          for (int i2 = 0; i2 < bs; i2++) {
              for (int j2 = 0; j2 < bs; j2++) {
                  Rblk[i2*N+j2] = Eblk[i2*N+j2] + (Dblk[i2*N+j2] * resultado);
              }
          }
      }
  }
}
