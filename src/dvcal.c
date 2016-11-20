/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"

// Scale a vector x by a scalar da and store it to output vector y: y=da*c
void dvcal(unsigned int n, const double da, const double *dx, double *dy)
{
	if(da == 1.0) {
		dcopy(n, dx, dy);
	}
	if(da == 0.0) {
		dset(n, 0.0, dy);
	}
	do {
		--n;
		dy[n] = da*dx[n];
	} while(n);
}