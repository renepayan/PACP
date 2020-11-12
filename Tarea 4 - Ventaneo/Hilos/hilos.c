#include <pthread.h>
#include "defs.h"
extern double *datos;
extern double *producto;
extern double *ventana;

void* funHilo( void *arg){
    register int i;
	int nh = *((int*) arg);	    
	for(i = nh; i < N; i+=NUM_HILOS){
		producto[i] = datos[i]*ventana[i];
	}
	pthread_exit(arg);
}