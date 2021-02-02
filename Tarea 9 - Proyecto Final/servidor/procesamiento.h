#ifndef PROCEAMIENTO_H
#define PROCEAMIENTO_H
#include "imagen.h"
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void llenarMascara(double *mascara);
void atiendeCliente( int cliente_sockfd, bmpInfoHeader *info, unsigned char *imagenGray, int tamImagen );
int iniServidor( );
#endif