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
extern pthread_mutex_t exclusor;
void* fun_hilo( void* arg){
	int nh = *(int*)arg;
	switch(nh){
		case 0:
			pthread_mutex_lock(&exclusor);
			ordenarConjunto(datos);
			pthread_mutex_unlock(&exclusor);
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
