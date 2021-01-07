#ifndef HILOS_H
#define HILOS_H

#include "imagen.h"
typedef struct{
    int numHilo;
    uint32_t width;
    uint32_t height;
    double *mascara;
    unsigned char *imagenG;
    unsigned char *imagenF;  
}parametroHilo;
void* funcionHilo(void* arg);
#endif