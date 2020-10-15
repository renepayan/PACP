#include <stdio.h>
#include "defs.h"
#include "procesamiento.h"
int procesoHijo(int np, int* datos){
	int mayor, menor, numeroDePares, promedio;
	switch(np){
		case 1:
			mayor = obtenerMayor(datos)
			exit(mayor);
		break;
		case 2:
			menor = obtenerMenor(datos)
			exit(mayor);
		break;
		case 3:
			numeroDePares = obtenerNumeroDePares(datos)
			exit(numeroDePares);
		break;
		case 4:
			promedio = (int)obtenerPromedio(datos)
			exit(promedio);
		break;
	}
}
void procesoPadre(){
	register int i;
	pid_t pid;
	int estado, respuesta;
	for(i = 0; i < NUM_PROC; i++){
		pid = wait(&estado);
		respuesta = estado << 8;
		printf("El proceso %d termino con la siguiente respuesta: %d\n",pid,respuesta);
	}	
}