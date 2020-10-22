#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "procesos.h"
#include "defs.h"
#include "helper.h"
int main(void){
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;
	int* datos = reservarMemoria();
	llenarArreglo(datos);
	printf("Este es el arreglo original:\n");
	imprimirArreglo(datos);	
	for(np = 0;np<NUM_PROC;np++){
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
			proceso_hijo(np, datos, &pipefd[np][0]);
		}
	}	
	proceso_padre(pipefd);
}
