#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "procesos.h"
#include "helper.h"

int main(void){	
	srand ( time(NULL) );
	int* A;
	int* B;
	pid_t pid;
	register int np;	
	int pipefd[NUM_PROC][2], edo_pipe;
	A = reservarMemoria();	
	B = reservarMemoria();	
	llenarArreglo(A);
	llenarArreglo(B);
	printf("El arreglo A es:\n");
    imprimirArreglo(A);
    printf("El arreglo B es:\n");
    imprimirArreglo(B);
	for(np = 0; np <  NUM_PROC; np++){
		edo_pipe = pipe(&pipefd[np][0]);
		if(edo_pipe == -1){
			printf("Error al crear la tuberia...\n");
			exit(EXIT_FAILURE);
		}	
		pid = fork();
		if( pid == -1){
			perror("Error al crear el proceso.....\n");
			exit(EXIT_FAILURE);
		}
		if( !pid ){
			proceso_hijo(np, &pipefd[np][0],A,B);
		}
	}
	long long int suma = proceso_padre(pipefd);
	printf("El producto punto es %lld\n",suma);
	free(A);
	free(B);
	return 0;
}
