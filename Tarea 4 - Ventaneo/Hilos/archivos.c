#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
void leerArchivo(double* datos, char* nombreArchivo){
    FILE *in_file  = fopen(nombreArchivo, "r");
    register int i;
    if( in_file == NULL){
        perror("Error al leer el archivo\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < N; i++){
        fscanf(in_file, "%lf", &datos[i]);
    }
    fclose(in_file);
}
void escribirArchivo(double* datos, char* nombreArchivo){
    FILE *out_file = fopen(nombreArchivo, "w");
    register int i;
    if(out_file == NULL){
        perror("Error al escribir el archivo\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < N; i++){
        fprintf(out_file, "%lf\n",datos[i]);
    }
    fclose(out_file);
}
