#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "defs.h"
double* reservarMemoria(){
	double* memoria = (double*)malloc(sizeof(double)*N);
	if(memoria == NULL){
		perror("Error al crear la memoria\n");
		exit(EXIT_FAILURE);
	}
	return memoria;
}
void llenarArreglo(double* arreglo){
	register int i;
	for(i = 0; i < N; i++){
		arreglo[i] = rand()%(INT_MAX/10);
	}
}
void imprimirArreglo(double* arreglo){
	register int i;
	for(i = 0; i < N; i++){		
		if(i%8 == 0 && i > 0){
			printf("\n");						
		}
		printf("%lf ",arreglo[i]);
	}	
	printf("\n");
}
