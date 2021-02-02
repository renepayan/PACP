#ifndef PROCEAMIENTO_H
#define PROCEAMIENTO_H
#include "imagen.h"
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void llenarMascara(double *mascara);
void recibirImagen( int sockfd, unsigned char *imagen, int tamImagen );
#endif