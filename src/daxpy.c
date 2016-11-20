/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"

// Add scalar times real vector x to real vector y: y=da*x+y
void daxpy (unsigned int n, const double da, const double *dx, double *dy)
{
	if(da == 0.0) {
		return;
	}
	if(da == 1.0) {
		do {
			--n;
			dy[n] += dx[n];
		} while(n);
	} else {
		do {
			--n;
			dy[n] += da*dx[n];
		} while(n);
	}
}