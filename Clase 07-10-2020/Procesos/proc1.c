#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_PROC 4
#define EVER 1
void proceso_hijo(int np);
void proceso_padre();
int main(void){
	//float num1 = 45, num2 = 13, suma, resta;
	pid_t pid;
	int np;
	printf("Probando procesos....\n");
	for( np = 0; np < NUM_PROC; np++){
		pid = fork();
		if( pid == -1){
			perror("Error al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		if( !pid ){
			proceso_hijo(np);
			/*printf("Proceso hijo ejecutado con pid: %d\n", getpid());
			suma = num1+num2;
			printf("La suma es: %f\n", suma);
			exit(22);*/
		}/*else{
			sleep(15);
			printf("Proceso padre con pid: %d\n", getpid());
			resta = num1-num2;
			printf("La resta es: %f\n", resta);
			pid = wait(&estado);
			printf("Proceso terminado con pid %d y estado %d\n",pid,estado>>8);
		}*/
	}
	proceso_padre();
	return 0;
}
void proceso_padre(){
	int np = 0, estado;
	pid_t pid;
	for(np = 0;np<NUM_PROC;np++){
		pid = wait(&estado);
		printf("Proceso hijo %d terminado con pid: %d terminado\n", estado<<8,pid);
	}
}	
void proceso_hijo(int np){
	for(;EVER;);
	exit(np);
}

