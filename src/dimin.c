/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"

// Return the index of the minimum value of the vector x and assign the vaue to the
// scalar minval
unsigned int dimin(unsigned int n, const double *dx, double *minval)
{
	double im;
	--n;
	im = n;
	*minval = dx[n];
	while(n) {
		--n;
		if(dx[n] < *minval) {
			*minval = dx[n];
			im = n;
		}
	}

	return im;
}