#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_PROC 2
#define N 32
#define EVER 1
void proceso_hijo(int np, int* datos);
void proceso_padre();
int* reservarMemoria();
void llenarArreglo(int* datos);
void imprimirArreglo(int *datos);
int buscarMenor(int* datos);
int buscarMayor(int* datos);

int main(void){
	pid_t pid;
	register int np;
	int* datos;
	printf("Probando procesos....\n");
	datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);
	for( np = 0; np < NUM_PROC; np++){
		pid = fork();
		if( pid == -1){
			perror("Error al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		if( !pid ){
			proceso_hijo(np, datos);
		}
	}
	proceso_padre();
	free(datos);
	return 0;
}
int buscarMayor(int* datos){
	register int i;
	int mayor = datos[0];
	for(i = 1;i<N;i++){
		if(datos[i]>mayor){
			mayor = datos[i];
		}
	}
	return mayor;
}
int buscarMenor(int* datos){
        register int i;
        int menor = datos[0];
        for(i = 1;i<N;i++){
                if(datos[i]<menor){
                        menor = datos[i];
                }
        }
        return menor;
}
void imprimirArreglo(int * datos){
	register int i;
	for(i = 0; i < N; i++){
		if(!(i%16))
			printf("\n");
		printf("%3d ",datos[i]);
	}
	printf("\n");
}

void llenarArreglo(int* datos){
	register int i;
	for(i = 0; i < N; i++){
		datos[i] = rand()%256;
	}
}
int* reservarMemoria(){
	int* mem;
	mem =  (int*)malloc(N*sizeof(int));
	if(!mem){
		perror("Error al asignar la memoria...\n");
		exit(EXIT_FAILURE);
	}
	return mem;
}
void proceso_padre(){
	register int np = 0;
	int estado;
	pid_t pid;
	for(np = 0;np<NUM_PROC;np++){
		pid = wait(&estado);
		printf("Proceso hijo %d terminado con pid: %d terminado\n", estado<<8,pid);
	}
}	
void proceso_hijo(int np, int* datos){
	//for(;EVER;);
	int mayor, menor;
	if( np == 0){
		mayor = buscarMayor(datos);
		exit(mayor);
	}else if(np == 1){
		menor = buscarMenor(datos);
		exit(menor);
	}
	exit(np);
}

