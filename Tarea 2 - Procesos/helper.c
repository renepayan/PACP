#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "defs.h"
int* reservarMemoria(){
	int* memoria = (int*)malloc(sizeof(int)*N);
	if(memoria == NULL){
		perror("Error al crear la memoria\n");
		exit(EXIT_FAILURE);
	}
	return memoria;
}
void llenarArreglo(int* arreglo){
	register int i;
	for(i = 0; i < N; i++){
		arreglo[i] = rand()%(INT_MAX/10);
	}
}
void imprimirArreglo(int* arreglo){
	register int i;
	for(i = 0; i < N; i++){		
		if(i%8 == 0 && i > 0){
			printf("\n");						
		}
		printf("%10d ",arreglo[i]);
	}	
	printf("\n");
}
