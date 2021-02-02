#include <math.h>

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