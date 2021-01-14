#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>


#include "imagen.h"
#include "helper.h"
#include "defs.h"
#include "hilos.h"
#include "procesamiento.h"


int main( ){		
	//Declaracion de variables
	char pathEntrada[256];
	char pathSalida[256];
	register int nh;
	pthread_t tids[NUM_HILOS];
	parametroHilo* hilo;
	unsigned char *imagenRGB, *imagenGray, *imagenFiltrada;
	bmpInfoHeader info;

	//Leer el archivo de entrada y salida
	printf("Ingrese la ruta de la imagen: ");
	scanf("%s", pathEntrada);
	printf("Ingrese la ruta de la salida: ");
	scanf("%s",pathSalida);

	//Cargar la imagen inicial
	imagenRGB = abrirBMP(pathEntrada, &info );

	//Mostrar la informacion con respecto a la imagen
	displayInfo( &info );
	
	//Reservar memoria para las imagenes (blanco y negro e imagen final)
	imagenGray = reservarMemoria( info.width, info.height );
    imagenFiltrada = reservarMemoria( info.width, info.height );
	//Inicializacion de la matriz final en blanco
    memset( imagenFiltrada, 255, info.width*info.height );

	//Convertir la imagen a escala de grises
    RGBToGray( imagenRGB, imagenGray, info.width, info.height );

	//Aplicar el filtro con los hilos
	for(nh = 0; nh < NUM_HILOS; nh++){
		parametroHilo *parametroParaPasar = (parametroHilo*)malloc(sizeof(parametroHilo));
		parametroParaPasar->height = info.height;
		parametroParaPasar->width = info.width;	
		parametroParaPasar->imagenG = imagenGray;
		parametroParaPasar->imagenF = imagenFiltrada;
		parametroParaPasar->numHilo = nh;
		printf("hilo %d creado\n",nh);
        if(pthread_create(  &tids[nh], NULL, funcionHilo,  parametroParaPasar )){
            perror("Error al crear el hilo\n");
            exit(EXIT_FAILURE);
	    }
	}
	for( nh = 0; nh < NUM_HILOS; nh++ ){
        pthread_join( tids[nh], (void**)&hilo);
		printf("Termino el hilo %d\n", hilo->numHilo);		
    }	

	//Regresar la imagen a "color" para ser almacenada
    GrayToRGB( imagenRGB ,imagenFiltrada, info.width, info.height );


	//Guardar la imagen en el destino
    guardarBMP(pathSalida, &info, imagenRGB );

    return 0;
}


