#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "hilos.h"
#include "helper.h"
#include "defs.h"
#include <time.h>
int* A;
int* B;
long long int suma;
int main(void){	
	srand(time(NULL));	
	int *hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	register int nh;
	suma = 0;
	A = reservarMemoria();	
	B = reservarMemoria();
	llenarArreglo(A);
	llenarArreglo(B);	
	printf("El arreglo A es:\n");
	imprimirArreglo(A);
	printf("El arreglo B es:\n");
	imprimirArreglo(B);
	for( nh = 0; nh < NUM_HILOS; nh++){
		nhs[nh] = nh;
		if(pthread_create(  &tids[nh], NULL, funHilo,  &nhs[nh] )){
			perror("Error al crear el hilo\n");
			exit(EXIT_FAILURE);
		}
	}
	for( nh = 0; nh < NUM_HILOS; nh++ ){
		pthread_join( tids[nh], (void**)&hilo);
		printf("Termino el hilo %d\n", *hilo);
	}	
	printf("El producto punto es %lld\n",suma);
	free(A);
	free(B);
	return 0;
}
