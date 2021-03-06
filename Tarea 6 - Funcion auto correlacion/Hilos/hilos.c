#include <pthread.h>
#include "defs.h"
#include "procesamiento.h"
extern double* datosPulsoCardiaco;
extern double* ventanaDeHann;
extern double* producto;
extern double* funcionDiscreta;

void* funHilo( void *arg){
    register int i;
	int nh = *((int*) arg);	    
	for(i = nh; i < N; i+=NUM_HILOS){		
		producto[i] = datosPulsoCardiaco[i]*ventanaDeHann[i];		
	}
	pthread_exit(arg);
}
void* funHiloDiscreta(void* arg){
	register int l;
	int nh = *((int*)arg);	
	int tamBloque = L/NUM_HILOS;
	int inicioBloque = tamBloque*nh;
	int finBloque = inicioBloque+tamBloque;	
	for(l = inicioBloque; l < finBloque; l++){
		funcionDiscreta[l] = rxx(l, producto);		
	}
	pthread_exit(arg);
}