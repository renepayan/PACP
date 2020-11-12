#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "defs.h"
void ventanaHann(int* datos){
	register int i;
	for(i = 0; i < N; i++){
		datos[i] = (int)(A0-A1*cos((2*M_PI*i)/(N-1)));
	}
}