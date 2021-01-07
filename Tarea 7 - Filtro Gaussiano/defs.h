#ifndef DEFS_H
#define DEFS_H
#define DIMASK 5
#define VARIANZA 1
#define NUM_HILOS 1
#include "imagen.h"
typedef struct parametroHiloTAG{
    int numHilo;
    uint32_t width;
    uint32_t height;
    double *mascara;
    unsigned char *imagenG;
    unsigned char *imagenF;  
}parametroHilo;
#endif
