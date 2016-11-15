/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"
#include <stdio.h>
// Return the minimum value of the vector x 
double dmin(unsigned int n, const double *dx)
{
	double minval;
	--n;
	minval = dx[n];
	while(n) {
		--n;
		if(dx[n] < minval) {
			minval = dx[n];
		}
	}

	return minval;
}