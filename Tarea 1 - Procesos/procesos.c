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
void procesoPadre(pid_t[3] pids){
	register int i;
	pid_t pid;
	int estado, respuesta;
	for(i = 0; i < NUM_PROC; i++){
		pid = wait(&estado);
		respuesta = estado << 8;
		printf("El proceso %d termino con la siguiente respuesta: %d",pid,respuesta);
		switch(pid){
			case pids[0]:
				printf(" (Estaba buscando el mayor)\n");
				break;
			case pids[1]:
				printf(" (Estaba buscando el menor)\n");
				break;
			case pids[2]:
				printf(" (Estaba buscando el numero de pares)\n");
				break;
			case pids[3]:
				printf(" (Estaba buscando el promedio)\n");
				break;				
		}
	}	
}
