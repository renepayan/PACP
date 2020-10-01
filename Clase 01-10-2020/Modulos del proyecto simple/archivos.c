/** @brief archivos.c
*	este archivo guarda un arreglo de datos en un archivo
*/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void guarda_datos(float datos[]){
	FILE* ap_archivo;
	register int n;
	ap_archivo = fopen("seno.dat","w");
	if(!ap_archivo){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	for(n = 0;n<MUESTRAS;n++){
		fprintf(ap_archivo, "%f \n",datos[n]);
	}
	fclose(ap_archivo);
}