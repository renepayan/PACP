#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
	float num1 = 45, num2 = 13, suma, resta;
	pid_t pid;
	int estado;
	printf("Probando procesos....\n");
	pid = fork();
	if( pid == -1){
		perror("Error al crear el proceso...\n");
		exit(EXIT_FAILURE);
	}
	if( !pid ){
		printf("Proceso hijo ejecutado con pid: %d\n", getpid());
		suma = num1+num2;
		printf("La suma es: %f\n", suma);
		exit(22);
	}else{
		printf("Proceso padre con pid: %d\n", getpid());
		resta = num1-num2;
		printf("La resta es: %f\n", resta);
		pid = wait(&estado);
		printf("Proceso terminado con pid %d y estado %d\n",pid,estado>>8);
	}
	return 0;
}	
