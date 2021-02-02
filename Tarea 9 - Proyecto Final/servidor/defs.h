#ifndef DEFS_H
#define DEFS_H
#define DIMASK 3
#define VARIANZA 1
#define NUM_HILOS 4
#include "imagen.h"
#define PUERTO 			5000	//Número de puerto asignado al servidor
#define COLA_CLIENTES 		5 	//Tamaño de la cola de espera para clientes
#define TAM_BUFFER 		100
#define EVER 			1

typedef struct parametroHiloTAG{
    int numHilo;
    uint32_t width;
    uint32_t height;
    unsigned char *imagenG;
    unsigned char *imagenF;  
}parametroHilo;
#endif
