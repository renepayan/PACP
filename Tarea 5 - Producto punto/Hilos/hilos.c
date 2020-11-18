#include <pthread.h>
#include <stdio.h>
#include "defs.h"

extern int *A;
extern int *B;
extern long long int suma;

void* funHilo( void *arg){	
    register int i;	
	int sumaLocal = 0;
	int nh = *((int*) arg);	    
	int tamBloque = N/NUM_HILOS;
	int inicioBloque = nh*tamBloque;
	int finBloque = inicioBloque+tamBloque;
	for(i = inicioBloque; i < finBloque; i++){
		sumaLocal+=(A[i]*B[i]);
	}
	printf("La suma local del hilo %d que abarca desde el %d hasta el %d es: %d\n",nh,inicioBloque,finBloque,sumaLocal);
	suma+=sumaLocal;
	pthread_exit(arg);
}
