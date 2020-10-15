#include "procesos.h"
#include "defs.h"
#include "helper.h"
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main(void){
	register int i;
	pid_t pid;
	int* datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);
	for(i = 0;i < NUM_PROC; i++){
		pid = fork();
		procesoHijo(i, datos);
	}
	procesoPadre();
}