#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "procesamiento.h"

int procesoHijo(int np, int* datos){
	int mayor, menor, numeroDePares, promedio;
	switch(np){
		case 1:
			mayor = obtenerMayor(datos);
			exit(mayor);
		break;
		case 2:
			menor = obtenerMenor(datos);
			exit(menor);
		break;
		case 3:
			numeroDePares = obtenerNumeroDePares(datos);
			exit(numeroDePares);
		break;
		case 4:
			promedio = (int)obtenerPromedio(datos);
			exit(promedio);
		break;
	}
	exit(np);
}
void procesoPadre(pid_t pids[3]){
	register int i;
	pid_t pid;
	int estado, respuesta;
	for(i = 0; i < NUM_PROC; i++){
		pid = wait(&estado);
		respuesta = estado << 8;
		printf("El proceso %d termino con la siguiente respuesta: %d",pid,respuesta);
		if((int)pid == (int)pids[0]){
			printf(" (Estaba buscando el mayor)\n");
		}else if((int)pid == (int)pids[1]){
			printf(" (Estaba buscando el menor)\n");
		}else if((int)pid == (int)pids[2]){
			printf(" (Estaba buscando el numero de pares)\n");
		}else if((int)pid == (int)pids[3]){
			printf(" (Estaba buscando el promedio)\n");
		}		
	}	
}
