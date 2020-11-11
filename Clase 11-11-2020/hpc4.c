#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_PROC 4
#define N 16

int* A;
int promedio;
void* ;




int main(void){
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;
	A = reservarMemoria();
	llnearArreglo(A);
	imprimirArreglo(A);
	printf("Probando procesos...\n");
	promedio = 0;
	for( np = 0; np < NUM_PROC; np++){
		edo_pipe = pipe(&pipefd[np][0]);
		if(edo_pipe == -1){
			perror("Error al crear la tuberia\n");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if(pid == -1){
			perror("Error al crear el proceso");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			proceso_hijo(np, &pipefd[np][0]);
		}
	}
	proceso_padre(pipefd);
	printf("El promedio es: %d\n",promedio);
	free(A);
}
void proceso_padre( int pipefd[NUM_PROC][2]){
	register int np;
	pid_t pid;
	int estado, numproc;
	int eleBloque = N/NUM_PROC, inicio;
	int suma_parcial = 0;
	for(np = 0; np < NUM_PROC; np++){
		pid = wait(&estado);
		numproc = estado>>8;
		close(pipefd[numproc][1]);
		//inicio = numproc*eleBloque;
		read(pipefd[numproc][0], &suma_parcial, sizeof(int));
		promedio+=suma_parcial;
		printf("Termino el proceso %d con pid: %d \n", numproc, pid);
		close pipefd[numproc][0] );
	}
	promedio = promedio >> 4;
}
void proceso_hijo(int np, int pipefd[]){	
	register int i;
	close( pipefd[0] );
	promedio = 0;
	for( i = np; i < N; i+=NUM_PROC){
		promedio+= A[i];
	}
	write(pipefd[1], &promedio, sizeof(int));
	close( pipefd[1] );
	exit(np);
}
