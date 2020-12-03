#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "defs.h"
void ventanaHann(double* datos){
	register int i;
	for(i = 0; i < N; i++){
		double valor = (A0-A1*cos((2*M_PI*i)/(N-1)));		
		datos[i] = valor;
	}
}
double rxx(int l, double* producto){
	double retorno = 0;
	register int n;
	for(n = l; n<N; n++){
		retorno+=producto[n]*producto[n-l];			
	}	
	return retorno;
}