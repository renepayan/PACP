#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include "imagen.h"
#include "helper.h"
#include "defs.h"
#include "hilos.h"
#include "procesamiento.h"

int finPrograma;
void manejador( int sig );
void iniSignals( );
int main( ){		
	//Declaracion de variables
	pid_t pid;
   	int cliente_sockfd, sockfd;
    bmpInfoHeader info;
    unsigned char *imagenRGB, *imagenGray, *imagenFiltrada;
	int tamImagen = 0;
	register int nh;
	pthread_t tids[NUM_HILOS];
	parametroHilo* hilo;			
	finPrograma = 0;
	iniSignals( );
	sockfd = iniServidor( );
	while(finPrograma == 0){
	   	printf ("En espera de peticiones de conexión ...\n");
   		if( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0 ){
			perror("Ocurrio algun problema al atender a un cliente");
			exit(1);
   		}
		pid = fork();
		if( !pid ){
			printf("Tomando foto\n");
			//Cargar la imagen inicial
			imagenRGB = abrirBMP("salida1.bmp", &info );

			//Mostrar la informacion con respecto a la imagen
			displayInfo( &info );
			
			//Reservar memoria para las imagenes (blanco y negro e imagen final)
			imagenGray = reservarMemoria( info.width, info.height );
			imagenFiltrada = reservarMemoria( info.width, info.height );
			//Inicializacion de la matriz final en blanco
			memset( imagenFiltrada, 255, info.width*info.height );

			//Convertir la imagen a escala de grises
			RGBToGray( imagenRGB, imagenGray, info.width, info.height );
			printf("Aplicando filtro\n");
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
			tamImagen = info.width * info.height;
			printf("Enviando imagen al servidor\n");
			atiendeCliente( cliente_sockfd, &info, imagenGray, tamImagen );
		}
	}
	close (sockfd);
	free( imagenRGB );
	free( imagenGray );
    return 0;
}
void manejador( int sig ){
	int estado;
	pid_t pid;
	if( sig == SIGCHLD ){
		printf("Se recibio la señal SIGCHLD en el servidor\n");
		pid = wait(&estado);
		printf("Termino el proceso %d con estado: %d\n", pid, estado>>8);
	}else if( sig == SIGINT ){
		printf("Se recibio la señal SIGINT en el servidor\n");
	   	printf("Concluimos la ejecución de la aplicacion Servidor \n");
		finPrograma = 1;
	}
}
void iniSignals( ){
	if( signal( SIGCHLD, manejador) == SIG_ERR ){
		perror("Error en el manejador");
		exit(EXIT_FAILURE);
	}

	if( signal( SIGINT, manejador) == SIG_ERR ){
		perror("Error en el manejador");
		exit(EXIT_FAILURE);
	}
}