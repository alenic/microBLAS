/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"

// Return the sum of absolute value of vector elements
double dasum(unsigned int n, const double *dx) {
	double sum = 0.0;
	do {
		--n;
		if(dx[n] < 0)
			sum = sum - dx[n];
		else
			sum = sum + dx[n];
	} while(n);

	return sum;
}