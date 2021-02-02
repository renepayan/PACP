#include <math.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
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
void recibirImagen( int sockfd, unsigned char *imagen, int tamImagen ){
	int bytesRecibidos;
	/* La función read regresa el número de bytes que se leyeron, la función read
	los bytes dentro de una trama mtu, la cual tenemos configurada por defecto con un
	tamaño de 1500 bytes */
	while( tamImagen > 0){ /* Si el tamaño de la imagen es mayor a cero, significa que aún siguen habiendo bytes sin leer*/
		bytesRecibidos = read (sockfd, imagen, tamImagen);    
		if( bytesRecibidos < 0){
			perror ("Ocurrio algun problema al recibir imagen del servidor");
			exit(1);
		}
		printf("Bytes recibidos: %d\n", bytesRecibidos);
		/* Actualizamos el tamaño de la imagen a leer, ya que ahora le restaremos los bytes que ya se leyeron*/
		tamImagen -= bytesRecibidos;
		/* El apuntador de la imagen también tiene que desplazarse, para que ahora
		el nuevo bloque de datos de la imagen se escriba en la siguiente dirección de memoria */
		imagen += bytesRecibidos;
	}
	

}