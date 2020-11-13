#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "archivos.h"
#include "procesamiento.h"
#include "hilos.h"
#include "helper.h"
#include "defs.h"
double* datos;
double* ventana;
double* producto;
int main(void){		
	int *hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	register int nh;
	datos = reservarMemoria();	
	ventana = reservarMemoria();
	producto = reservarMemoria();
	leerArchivo(datos, "PulseSensor.dat");	
	ventanaHann(ventana);
	for( nh = 0; nh < NUM_HILOS; nh++){
		nhs[nh] = nh;
		if(pthread_create(  &tids[nh], NULL, funHilo,  &nhs[nh] )){
			perror("Error al crear el hilo\n");
			exit(EXIT_FAILURE);
		}
	}
	for( nh = 0; nh < NUM_HILOS; nh++ ){
		pthread_join( tids[nh], (void**)&hilo);
		printf("Termino el hilo %d\n", *hilo);
	}	
	printf("Guardando la ventana\n");
	escribirArchivo(ventana, "ventana.dat");
	printf("Guardando el producto\n");
	escribirArchivo(producto, "producto.dat");
	free(ventana);
	free(datos);
	free(producto);
	return 0;
}
