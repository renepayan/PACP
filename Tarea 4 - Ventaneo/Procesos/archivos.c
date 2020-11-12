#include "defs.h"
void leerArchivo(int* datos, char* nombreArchivo){
    FILE *in_file  = fopen(nombreArchivo, "r");
    register int i;
    if( in_file == NULL){
        perror("Error al leer el archivo\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < N; i++){
        fscanf(fp, "%d", datos[i]);
    }
    fclose(in_file);
}