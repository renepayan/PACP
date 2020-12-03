#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "hilos.h"
#include "helper.h"
#include "defs.h"
#include "archivos.h"
#include "procesamiento.h"
double* datosPulsoCardiaco;
double* ventanaDeHann;
double* producto;
double* funcionDiscreta;
long long int suma;
pthread_mutex_t exclusor;
int main(void){
	//Parametros de los hilos
	int *hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	register int nh;
	pthread_mutex_init(&exclusor, NULL);	
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
	//Aqui se calcula el producto mediante hilos
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
	//Aqui se guarda el producto
	printf("Guardando el producto\n");
	escribirArchivo(producto, "producto.dat");	
	//Ahora mando a generar la funcion discreta
	for( nh = 0; nh < NUM_HILOS; nh++){            
            if(pthread_create(  &tids[nh], NULL, funHiloDiscreta,  &nhs[nh] )){
                    perror("Error al crear el hilo\n");
                    exit(EXIT_FAILURE);
	        }
    }
    for( nh = 0; nh < NUM_HILOS; nh++ ){
        pthread_join( tids[nh], (void**)&hilo);
		printf("Termino el hilo %d\n", *hilo);
    }       
	//Aqui se guarda la funcion discreta
	printf("Guardando la funcion discreta\n");
	escribirArchivo(funcionDiscreta, "funcionDiscreta.dat");	
	free(datosPulsoCardiaco);
	free(funcionDiscreta);
	free(producto);
	free(ventanaDeHann);
	return 0;
}
