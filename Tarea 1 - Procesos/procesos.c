#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "procesamiento.h"
#include <sys/types.h>
#include <unistd.h>
int procesoHijo(int np, int* datos){	
	int mayor, menor, numeroDePares, promedio;
	switch(np){
		case 0:
			mayor = obtenerMayor(datos);
			exit(mayor);
		break;
		case 1:
			menor = obtenerMenor(datos);
			exit(menor);
		break;
		case 2:
			numeroDePares = obtenerNumeroDePares(datos);
			exit(numeroDePares);
		break;
		case 3:			
			promedio = (int)obtenerPromedio(datos);
			exit(promedio);
		break;
	}
	exit(0);
}
void procesoPadre(pid_t pids[4]){
	register int i;
	pid_t pid;
	int estado;
	for(i = 0; i < NUM_PROC; i++){
		pid = wait(&estado);		
		printf("El proceso %d termino con la siguiente respuesta: %d",pid,estado >> 8);
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
