#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROC 4

void proceso_padre(int pipefd[NUM_PROC][2] );
void proceso_hijo(int np, int pipefd[]);

int main(){
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;
	printf("Probando procesos....\n");	
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
			proceso_hijo(np, &pipefd[np][0]);
		}
	}
	proceso_padre(pipefd);
}
void proceso_padre(int pipefd[NUM_PROC][2]){
	register int np;
	pid_t pid;
	int estado, numproc, resultado;
	for(np = 0; np < NUM_PROC; np++){
		pid = wait(&estado);		
		numproc = estado >> 8;
		close( pipefd[numproc][1] );
		read( pipefd[numproc][0], &resultado, sizeof(int) );				
		if( numproc == 0){
			printf("Termino el proceso %d con pid: %d\n",numproc,pid);
			printf("La suma es %d\n",resultado);
		}else if( numproc == 1){
			printf("Termino el proceso %d con pid: %d\n",numproc,pid);
            printf("La resta es %d\n",resultado);
		}else if( numproc == 2){
			printf("Termino el proceso %d con pid: %d\n",numproc,pid);
            printf("La multiplicacion es %d\n",resultado);
		}else if( numproc == 3){
			printf("Termino el proceso %d con pid: %d\n",numproc,pid);
            printf("La division es %d\n",resultado);
		}
		close( pipefd[numproc][0] );
	}	
}
void proceso_hijo(int np, int pipefd[]){
	int num1 = 20, num2 = 4;
	int suma, resta, multi, divi;
	close(pipefd[0]);
	if( np == 0){
		suma = num1+num2;
		write(pipefd[1], &suma, sizeof(int));
	}else if(np == 1){
		resta = num1-num2;
		 write(pipefd[1], &resta, sizeof(int));
	}else if(np == 2){
		multi = num1*num2;
		 write(pipefd[1], &multi, sizeof(int));
	}else if(np == 3){
		divi = num1/num2;
		 write(pipefd[1], &divi, sizeof(int));
	}
	close( pipefd[1] );
	exit(np);
}
