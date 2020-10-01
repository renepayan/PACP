/** @brief procesamiento.c
*	este archivo guarda un arreglo de datos en un archivo
*/

#include <stdio.h>
#include <math.h>
#include "defs.h"

void genera_seno(float datos[]){
	float f = 1000, fs = 45000;
	register int n;
	for( n = 0;n < MUESTRAS; n++){
		seno[n] = sinf(2*n*M_PI*f/fs);
	}
}