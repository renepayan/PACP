#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "archivos.h"
#include "procesamiento.h"
#include "procesos.h"
#include "helper.h"
double* datos;
double* ventana;
double* producto;
int main(void){	
	pid_t pid;
	register int np;	
	int pipefd[NUM_PROC][2], edo_pipe;
	datos = reservarMemoria();	
	ventana = reservarMemoria();
	producto = reservarMemoria();
	leerArchivo(datos, "PulseSensor.dat");	
	ventanaHann(ventana);
	for(np = 0; np <  NUM_PROC; np++){
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
	imprimirArreglo(producto);
	return 0;
}
