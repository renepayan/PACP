#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "defs.h"
#include "helper.h"
void proceso_hijo(int np, int pipefd[], int *A, int *B){
	close(pipefd[0]);
	int* sumaLocal = (int*)malloc(sizeof(int));
	register int i;	
	for(i = np; i < N; i+=NUM_PROC){
		*sumaLocal+=A[i]*B[i];
	}		
	write(pipefd[1], sumaLocal, sizeof(int));
	close(pipefd[1]);
	exit(np);
}
long long int proceso_padre(int pipefd[NUM_PROC][2] ){	
	long long int pp = 0;
	register int i;	
	int estado, numproc;
	int* retorno = (int*)malloc(sizeof(int));
	pid_t pid;		
	for(i = 0; i < NUM_PROC; i++){
		pid = wait(&estado);		
		numproc = estado >> 8;		
		close( pipefd[numproc][1] );
		read( pipefd[numproc][0], retorno, sizeof(int) );							
		printf("Termino el proceso %d con pid %d y su suma intercalada es de: %d\n", numproc, pid, *retorno);		
		pp+=(long long int)(*retorno);		
		close( pipefd[numproc][0] );
	}		
	return pp;
}
