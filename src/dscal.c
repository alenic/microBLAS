/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"

// Scale a vector by a scalar da: y=da*y
void dscal(unsigned int n, const double da, double *dy)
{
	if(da == 1.0) {
		return;
	}
	if(da == 0.0) {
		dset(n, 0.0, dy);
	}
	do {
		--n;
		dy[n] = da*dy[n];
	} while(n);
}