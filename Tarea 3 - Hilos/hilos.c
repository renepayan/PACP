#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include "defs.h"
#include "helper.h"
#include "procesamiento.h"
extern int *datos;
extern int numeroDePares;
extern int promedio;
extern int numeroDePrimos;
void* fun_hilo( void* arg){
	int nh = *(int*)arg;	
	switch(nh){
		case 0:
			ordenarConjunto(datos);
		break;
		case 1:
			promedio = obtenerPromedio(datos);
		break;
		case 2:
			numeroDePares = obtenerNumeroDePares(datos);
		break;
		case 3:
			numeroDePrimos = obtenerNumeroDePrimos(datos);
		break;
	}
	pthread_exit(arg);
}