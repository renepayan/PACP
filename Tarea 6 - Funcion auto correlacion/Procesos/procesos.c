#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "defs.h"
#include "helper.h"
#include "procesamiento.h"
extern double* datosPulsoCardiaco;
extern double* ventanaDeHann;
extern double* producto;
extern double* funcionDiscreta;
void proceso_hijo(int np, int pipefd[]){
	close(pipefd[0]);
	double* retorno = malloc((N/NUM_PROC)*sizeof(double));	
	register int i;
	int tamanio = N/NUM_PROC;
	int inicioArreglo = np*tamanio;
	int finArreglo = inicioArreglo + tamanio;	
	for(i = inicioArreglo; i < finArreglo; i++){
		retorno[i - inicioArreglo] = datosPulsoCardiaco[i]*ventanaDeHann[i]; 
	}	
	write(pipefd[1], retorno, sizeof(double)*(N/NUM_PROC));
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
		inicio = np*tamanio;
		fin = inicio + tamanio;
		for(i = inicio; i < fin; i++){
			producto[i] = retorno[i-inicio];
		}
		close( pipefd[numproc][0] );
	}		
}
void procesoHijoFuncionDiscreta(int np, int pipefd[]){		
	close(pipefd[0]);	
	register int l;
	register int n;
	double* retorno = malloc((L/NUM_PROC)*sizeof(double));
	int tamanio = L/NUM_PROC;
	int inicioArreglo = np*tamanio;
	int finArreglo = inicioArreglo + tamanio;				
	for(l = inicioArreglo; l < finArreglo; l++){
		retorno[l - inicioArreglo] = 0;
		for(n = l; n<N; n++){
			retorno[l-inicioArreglo]+=producto[n]*producto[n-l];			
		}				
	}			
	write(pipefd[1], retorno, sizeof(double)*(L/NUM_PROC));
	close(pipefd[1]);
	exit(np);
}

void proceso_padre_funcion_discreta(int pipefd[NUM_PROC][2] ){	
	register int np;
	register int i;
	int estado, numproc, inicio, fin, tamanio;
	double* retorno = malloc((L/NUM_PROC)*sizeof(double));	
	pid_t pid;		
	tamanio = L/NUM_PROC;
	for(np = 0; np < NUM_PROC; np++){
		pid = wait(&estado);		
		numproc = estado >> 8;		
		close( pipefd[numproc][1] );
		read( pipefd[numproc][0], retorno, sizeof(double)*tamanio );									
		inicio = numproc*tamanio;
		fin = inicio + tamanio;
		printf("Termino el proceso %d con pid %d que abarca desde %d hasta %d\n", numproc, pid, inicio, fin);				
		for(i = inicio; i < fin; i++){
			funcionDiscreta[i] = retorno[i-inicio];
		}
		close( pipefd[numproc][0] );
	}		
}