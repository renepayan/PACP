#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
void ordenarConjunto(int* datos){
	register int i;
	register int j;
	if(N>0){		
		for(i =0; i < N; i++){
			for(j = 0; j < N-1; j++){
				if(datos[j]>datos[j+1]){					
					int temp = datos[j+1];
					datos[j+1] = datos[j];
					datos[j] = temp;
				}
			}
		}				
	}else{
		perror("No hay suficientes datos\n");
		exit(EXIT_FAILURE);
	}
}
void multiplicarConjunto(int* datos){
	register int i;
	if(N>0){		
		for(i =0; i < N; i++){
			datos[i] = datos[i]*10;
				
		}		
	}else{
		perror("No hay suficientes datos\n");
		exit(EXIT_FAILURE);
	}
}
int obtenerPromedio(int* datos){
	register int i;
	if(N>0){
		long long int suma = 0;
		for(i = 0; i < N; i++){
			suma += datos[i];
		}
		return (int)(suma/(long long int)N);
	}else{
		perror("No hay suficientes datos\n");
		exit(EXIT_FAILURE);
	}
}
int obtenerNumeroDePares(int* datos){
	register int i;
	if(N>0){
		int numeroDePares = 0;
		for(i = 0; i < N; i++){
			if(datos[i] % 2 == 0){
				numeroDePares += 1;
			}
		}
		return numeroDePares;
	}else{
		perror("No hay suficientes datos\n");
		exit(EXIT_FAILURE);
	}
}
int obtenerNumeroDePrimos(int* datos){
	register int i,j;
	int numPrimos = 0;	
	for(i = 0;i<N;i++){		
		int sePuede = 1;
		if(datos[i] > 1) {
			for(j = 2;j<datos[i];j++){
				if(datos[i]%j == 0){					
					sePuede = 0;
					break;
				}
			}	
			if(sePuede){
				printf("El numero %d es primo\n", datos[i]);
				numPrimos++;
			}
		}		
	}
	return numPrimos;
}