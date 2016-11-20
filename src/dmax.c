/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"

// Return the maximum value of the vector x 
double dmax(unsigned int n, const double *dx)
{
	double maxval;
	--n;
	maxval = dx[n];
	while(n) {
		--n;
		if(dx[n] > maxval) {
			maxval = dx[n];
		}
	}

	return maxval;
}