/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"
#include <math.h>

// Return the norm of a vector x: sqrt(x'*x)
double dnorm(unsigned int n, const double *dx) {
	double sum=0.0;

	do {
		--n;
		sum += dx[n]*dx[n];
	} while(n);

	return sqrt(sum);
}