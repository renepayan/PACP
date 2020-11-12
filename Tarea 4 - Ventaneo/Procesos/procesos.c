#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "defs.h"
#include "helper.h"
#include "procesamiento.h"
extern double* datos;
extern double* ventana;
extern double* producto;
void proceso_hijo(int np, int pipefd[]){
	close(pipefd[0]);
	double* retorno = malloc((N/NUM_PROC)*sizeof(double));	
	register int i;
	int tamanio = N/NUM_PROC;
	int inicioArreglo = np*tamanio;
	int finArreglo = inicioArreglo + tamanio;	
	for(i = inicioArreglo; i < finArreglo; i++){
		retorno[i - inicioArreglo] = datos[i]*ventana[i]; 
	}	
	write(pipefd[1], retorno, sizeof(double)*N);
	close(pipefd[1]);
	exit(np);
}
void proceso_padre(int pipefd[NUM_PROC][2] ){	
	register int np;
	register int i;
	int estado, numproc, inicio, fin, tamanio;
	double* retorno = malloc((N/NUM_PROC)*sizeof(double));	
	pid_t pid;		
	tamanio = N/NUM_PROC;
	for(np = 0; np < NUM_PROC; np++){
		pid = wait(&estado);		
		numproc = estado >> 8;
		printf("Termino el proceso %d con pid %d\n", numproc, pid);		
		close( pipefd[numproc][1] );
		read( pipefd[numproc][0], retorno, sizeof(double)*tamanio );							
		//imprimirArreglo(retorno);		
		inicio = np*tamanio;
		fin = inicio + tamanio;
		for(i = inicio; i < fin; i++){
			producto[i] = retorno[i-inicio];
		}
		close( pipefd[numproc][0] );
	}		
}
