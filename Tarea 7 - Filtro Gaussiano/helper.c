#include <stdlib.h>

#include "imagen.h"
#include "defs.h"

unsigned char * reservarMemoria( uint32_t width, uint32_t height ){
	unsigned char *imagen;
	imagen = (unsigned char *)malloc( width*height*sizeof(unsigned char) );
	if( imagen == NULL ){
		perror("Error al asignar memoria a la imagen");
		exit(EXIT_FAILURE);
	}
	return imagen;
}

double* reservarMemoriaMascara(){
    double *mascara;
    mascara = malloc(sizeof(double)*(DIMASK*DIMASK));
    if(mascara == NULL){
        perror("Error al asignar memoria a la mascara");
		exit(EXIT_FAILURE);
    }
    return mascara;
}