#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "imagen.h"
#include "helper.h"
#include "defs.h"
#include "hilos.h"
#include "procesamiento.h"


int main( ){		
	//Declaracion de variables
	unsigned char *imagenRGB, *imagen;
	bmpInfoHeader info;
	int sockfd;
	struct sockaddr_in direccion_servidor;

	memset (&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);
	
	if( inet_pton(AF_INET, DIR_IP, &direccion_servidor.sin_addr) <= 0 ){
		perror("Ocurrio un error al momento de asignar la direccion IP");
		exit(1);
	}
	printf("Creando Socket ....\n");
	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 ){
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
	}
	printf ("Estableciendo conexion ...\n");
	if( connect(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0) {
		perror ("Ocurrio un problema al establecer la conexion");
		exit(1);
	}
	printf ("Recibiendo la estructura info de la imagen del servidor ...\n");
	if (read (sockfd, &info, sizeof(bmpInfoHeader)) < 0){
		perror ("Ocurrio algun problema al recibir del tamaño de la imagen del servidor");
		exit(1);
	}
	imagen    = reservarMemoria( info.width*info.height );
	imagenRGB = reservarMemoria( info.width*info.height*3 );
	printf ("Recibiendo la imagen del servidor ...\n");
	recibirImagen( sockfd, imagen, info.width*info.height );
	GrayToRGB( imagenRGB, imagen, info.width, info.height);
	guardarBMP( "salida.bmp", &info, imagenRGB );

	printf("El servidor recibio la imagen\n");
	printf ("Cerrando la aplicacion cliente\n");	

    return 0;
}


