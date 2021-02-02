#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "imagen.h"
#include "defs.h"

void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
    int indiceRGB, indiceGray;
	for( indiceGray = 0, indiceRGB = 0; indiceGray < (height*width); indiceGray++, indiceRGB += 3 ){
		imagenRGB[indiceRGB]   = imagenGray[indiceGray];
		imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
		imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
	}
}
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height ){
	unsigned char nivelGris;
	int indiceRGB, indiceGray;
	for( indiceGray = 0, indiceRGB = 0; indiceGray < (height*width); indiceGray++, indiceRGB += 3 ){
		nivelGris = (30*imagenRGB[indiceRGB] + 59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2]) / 100;
		imagenGray[indiceGray] = nivelGris;
	}
}
void llenarMascara(double *mascara){
    register int i, j;
    double razonX, razonY, division, exponente;
    for(i = 0; i < DIMASK; i++){            
        for(j = 0; j < DIMASK; j++){
            division = (double)2.0 * VARIANZA;
            razonX = (double)( (-DIMASK/2+i) * (-DIMASK/2+i) );
            razonY = (double)( (-DIMASK/2+j) * (-DIMASK/2+j) );
            exponente = -((razonX+razonY)/division);
            mascara[DIMASK*i+j] = ((double)1.0/(double)(2*M_PI*VARIANZA))*exp(exponente);	
        }		
    }	
}

int iniServidor( ){
   	struct sockaddr_in direccion_servidor; //Estructura de la familia AF_INET, que almacena direccion
	int sockfd;
/*
 *	AF_INET - Protocolo de internet IPV4
 *  htons - El ordenamiento de bytes en la red es siempre big-endian, por lo que
 *  en arquitecturas little-endian se deben revertir los bytes
 *  INADDR_ANY - Se elige cualquier interfaz de entrada
 */
   	memset (&direccion_servidor, 0, sizeof (direccion_servidor));	//se limpia la estructura con ceros
   	direccion_servidor.sin_family 		= AF_INET;
   	direccion_servidor.sin_port 		= htons(PUERTO);
   	direccion_servidor.sin_addr.s_addr 	= INADDR_ANY;
/*
 *	Creacion de las estructuras necesarias para el manejo de un socket
 *  SOCK_STREAM - Protocolo orientado a conexión
 */
   	printf("Creando Socket ....\n");
   	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
   	}
/*
 *  bind - Se utiliza para unir un socket con una dirección de red determinada
 */
   	printf("Configurando socket ...\n");
   	if( bind(sockfd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0 )
	{
		perror ("Ocurrio un problema al configurar el socket");
		exit(1);
   	}
/*
 *  listen - Marca al socket indicado por sockfd como un socket pasivo, esto es, como un socket
 *  que será usado para aceptar solicitudes de conexiones de entrada usando "accept"
 *  Habilita una cola asociada la socket para alojar peticiones de conector procedentes
 *  de los procesos clientes
 */
   	printf ("Estableciendo la aceptacion de clientes...\n");
	if( listen(sockfd, COLA_CLIENTES) < 0 )
	{
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
		exit(1);
   	}

	return sockfd;
}
void atiendeCliente( int cliente_sockfd, bmpInfoHeader *info, unsigned char *imagenGray, int tamImagen ){
    printf("Se aceptó un cliente, enviando cabezera... \n");
    if( write (cliente_sockfd, info, sizeof(bmpInfoHeader)) < 0 ){
		perror("Ocurrio un problema en el envio de la cabezera");
		exit(EXIT_FAILURE);
    }
	printf("Se aceptó un cliente, enviando imagen... \n");
	if( write (cliente_sockfd, imagenGray, tamImagen) < 0 ){
		perror("Ocurrio un problema en el envio de la imagen");
		exit(EXIT_FAILURE);
    }
	close (cliente_sockfd);
	exit(0);
}