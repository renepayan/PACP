#include <stdio.h>
#include <math.h>
#include <pthread.h> 

#include "defs.h"
#include "helper.h"
#include "imagen.h"

void* funcionHilo(void* arg){
    parametroHilo *parametrosEntrada = (parametroHilo*) arg;    
    register int x, y, xm, ym;
    int indicei, indicem;
    int inicioHilo, finHilo, conv;
    inicioHilo = (parametrosEntrada->height/NUM_HILOS)*parametrosEntrada->numHilo;    
    finHilo = (parametrosEntrada->numHilo == NUM_HILOS-1)?parametrosEntrada->height-DIMASK:inicioHilo+(parametrosEntrada->height/NUM_HILOS)-DIMASK;    
    for( y = inicioHilo; y <= finHilo; y++ ){
		for( x = 0; x <= parametrosEntrada->width-DIMASK; x++ ){			
			indicem = 0;
			conv = 0;
			for( ym = 0; ym < DIMASK; ym++ )
				for( xm = 0; xm < DIMASK; xm++ ){
					indicei = (y+ym)*parametrosEntrada->width + (x+xm);
					conv += ((double)parametrosEntrada->imagenG[indicei] * parametrosEntrada->mascara[indicem++]);
				}			
			indicei = (y+1)*parametrosEntrada->width + (x+1);
			parametrosEntrada->imagenF[indicei] = conv;
		}
    }
    printf("hola soy el hilo %d y abarco desde %d hasta %d\n", parametrosEntrada->numHilo, inicioHilo, finHilo);
    pthread_exit(arg);
    return NULL;
}