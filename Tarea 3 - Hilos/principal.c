#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include "hilos.h"
#include "defs.h"
#include "helper.h"
#include "procesamiento.h"
int* datos;
int numeroDePares;
int promedio;
int numeroDePrimos;
int main(void){	
	register int nh;	
	int* hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	
	
	datos = reservarMemoria();
	llenarArreglo(datos);
	printf("Este es el arreglo original:\n");
	imprimirArreglo(datos);		
	for(nh = 0;nh<NUM_HILOS;nh++){
		nhs[nh] = nh;
		pthread_create(  &tids[nh], NULL, fun_hilo, &nhs[nh] );
	}		
	for( nh = 0; nh < NUM_HILOS; nh++ ){		
		pthread_join( tids[nh], (void**)&hilo);
		printf("Termino el hilo %d\n", *hilo);		
		switch(*hilo){
			case 0:
				printf("Este es el arreglo final:\n");
				imprimirArreglo(datos);	
			break;
			case 1:
				printf("El promedio del arreglo es %d\n",promedio);
			break;
			case 2:
				printf("Hay %d pares en el arreglo\n",numeroDePares);
			break;
			case 3:
				printf("Hay %d primos en el arreglo\n",numeroDePrimos);
			break;
		}
	}
}
