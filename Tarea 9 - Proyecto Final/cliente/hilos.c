#include <stdio.h>
#include <math.h>
#include <pthread.h> 

#include "defs.h"
#include "helper.h"
#include "imagen.h"

void* funcionHilo(void* arg){
    parametroHilo *parametrosEntrada = (parametroHilo*) arg;    
    register int x, y, xm, ym;
    int indicei, indicem, inicioHilo, finHilo,convFil, convCol;
    int gradienteFila[DIMASK*DIMASK] = {
      1, 0, -1,
      2, 0, -2,
      1, 0, -1
    };
    int gradienteColumna[DIMASK*DIMASK] = {
      -1, -2, -1,
      0,  0,  0,
      1,  2,  1
    };
    inicioHilo = (parametrosEntrada->height/NUM_HILOS)*parametrosEntrada->numHilo;    
    finHilo = (parametrosEntrada->numHilo == NUM_HILOS-1)?parametrosEntrada->height-DIMASK:inicioHilo+(parametrosEntrada->height/NUM_HILOS)-1;    

    for( y = inicioHilo; y <= finHilo; y++ ){
      for( x = 0; x <= parametrosEntrada->width-DIMASK; x++ ){			
        indicem = 0;
			  convFil = 0;
			  convCol = 0;
			  for( ym = 0; ym < DIMASK; ym++ ){
				  for( xm = 0; xm < DIMASK; xm++ ){
					  indicei = (y+ym)*parametrosEntrada->width + (x+xm);
					  convFil += parametrosEntrada->imagenG[indicei] * gradienteFila[indicem];
					  convCol += parametrosEntrada->imagenG[indicei] * gradienteColumna[indicem++];
				  }
        }
			  convFil = convFil >> 2;
			  convCol = convCol >> 2;
			  indicei = (y+1)*parametrosEntrada->width + (x+1);
			  parametrosEntrada->imagenF[indicei] = (unsigned char)sqrt( (convFil * convFil) + (convCol * convCol) );
      }
    }
    printf("hola soy el hilo %d y abarco desde %d hasta %d\n", parametrosEntrada->numHilo, inicioHilo, finHilo);
    pthread_exit(arg);
    return NULL;
}