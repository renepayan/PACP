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

int finPrograma;
int main( ){		
	//Declaracion de variables
	pid_t pid;
   	int cliente_sockfd, sockfd;
    bmpInfoHeader info;
    unsigned char *imagenRGB, *imagenGray;
	int tamImagen;
	//Cargar la imagen inicial
	imagenRGB = abrirBMP("huella1.bmp", &info );

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
	finPrograma = 0;
	iniSignals( );
	sockfd = iniServidor( );
	for( ; !finPrograma ; ){
	   	printf ("En espera de peticiones de conexión ...\n");
   		if( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0 ){
			perror("Ocurrio algun problema al atender a un cliente");
			exit(1);
   		}
		pid = fork();
		if( !pid ){
			atiendeCliente( cliente_sockfd, imagenGray, tamImagen );
		}
	}
	close (sockfd);
	free( imagenRGB );
	free( imagenGray );
    return 0;
}
