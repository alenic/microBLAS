/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"

// Return the dot product of two vector: x1'*x2
double ddot(unsigned int n, const double *dx1, const double *dx2) {
	double sum=0.0;

	do {
		--n;
		sum += dx1[n]*dx2[n];
	} while(n);

	return sum;
}