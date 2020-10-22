#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "defs.h"
#include "helper.h"
#include "procesamiento.h"
void proceso_hijo(int np, int* datos, int pipefd[]){
	close(pipefd[0]);	
	static int promedio, numeroDePares;	
	switch(np){
		case 0:						
			ordenarConjunto(datos);									
			write(pipefd[1], datos, sizeof(int)*N);
		break;
		case 1:
			multiplicarConjunto(datos);				
			write(pipefd[1], datos, sizeof(int)*N);
		break;
		case 2:
			numeroDePares = obtenerNumeroDePares(datos);			
			write(pipefd[1], &numeroDePares, sizeof(int));
		break;
		case 3:			
			promedio = obtenerPromedio(datos);						
			write(pipefd[1], &promedio, sizeof(int));
		break;
	}
	close(pipefd[1]);
	exit(np);
}
void proceso_padre(int pipefd[NUM_PROC][2] ){	
	register int np;
	pid_t pid;
	int estado, numproc;
	int resultado;
	int* datos = reservarMemoria();
	for(np = 0; np < NUM_PROC; np++){
		pid = wait(&estado);		
		numproc = estado >> 8;
		close( pipefd[numproc][1] );				
		if( numproc == 0){			
			read( pipefd[numproc][0], datos, sizeof(int)*N );	
			printf("Termino el proceso %d con pid: %d\n",numproc,pid);	
			printf("Este es el arreglo ordenado:\n");
            imprimirArreglo(datos);
		}else if( numproc == 1){
			read( pipefd[numproc][0], datos, sizeof(int)*N );	
			printf("Termino el proceso %d con pid: %d\n",numproc,pid);			
			printf("Este es el arreglo multiplicado:\n");
            imprimirArreglo(datos);			
		}else if( numproc == 2){
			read( pipefd[numproc][0], &resultado, sizeof(int) );	
			printf("Termino el proceso %d con pid: %d\n",numproc,pid);
            printf("El numero de pares es %d\n",resultado);
		}else if( numproc == 3){
			read( pipefd[numproc][0], &resultado, sizeof(int) );	
			printf("Termino el proceso %d con pid: %d\n",numproc,pid);			
            printf("El promedio es %d\n",resultado);
		}
		close( pipefd[numproc][0] );
	}	
}
