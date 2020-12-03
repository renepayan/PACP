#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "procesos.h"
#include "helper.h"
#include "defs.h"
#include "archivos.h"
#include "procesamiento.h"
double* datosPulsoCardiaco;
double* ventanaDeHann;
double* producto;
double* funcionDiscreta;
int main(void){
	//Parametros de los procesos
	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2],edo_pipe, pipefd1[NUM_PROC][2];
	//Aqui reservo la memoria
	datosPulsoCardiaco = reservarMemoria();	
	ventanaDeHann = reservarMemoria();
	producto = reservarMemoria();
	funcionDiscreta = reservarMemoria();
	//Aqui leo el archivo de entrada del sensor de pulso
	leerArchivo(datosPulsoCardiaco, "PulseSensor.dat"); 	 
	//Restar el offset
	restarOffset(datosPulsoCardiaco);
	//Genero la ventana de hann
    ventanaHann(ventanaDeHann);
	//Guardo la ventana de Hann
	printf("Guardando la ventana\n");
    escribirArchivo(ventanaDeHann, "ventana.dat");
	printf("Calculando el producto\n");
	//Aqui se calcula el producto mediante procesos
	for(np = 0; np <  NUM_PROC; np++){
        edo_pipe = pipe(&pipefd[np][0]);
        if(edo_pipe == -1){
	        perror("Error al crear la tuberia...\n");
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
	//Aqui se guarda el producto
	printf("Guardando el producto\n");
	escribirArchivo(producto, "producto.dat");	
	//Ahora mando a generar la funcion discreta
	for(np = 0; np <  NUM_PROC; np++){
        edo_pipe = pipe(&pipefd1[np][0]);
        if(edo_pipe == -1){
	        perror("Error al crear la tuberia...\n");
            exit(EXIT_FAILURE);
        }       
        pid = fork();
        if( pid == -1){
            perror("Error al crear el proceso.....\n");
            exit(EXIT_FAILURE);
        }
        if( !pid ){			
            procesoHijoFuncionDiscreta(np, &pipefd1[np][0]);
		}
	}
	proceso_padre_funcion_discreta(pipefd1);
	//Aqui se guarda la funcion de auto correlacion
	printf("Guardando la funcion discreta\n");
	escribirArchivo(funcionDiscreta, "funcionDiscreta.dat");	
	free(datosPulsoCardiaco);
	free(funcionDiscreta);
	free(producto);
	free(ventanaDeHann);
	return 0;
}
