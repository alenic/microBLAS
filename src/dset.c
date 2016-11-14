/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"

#include "microBLAS.h"

// Set a vector y to a constant value a: y[i]=a (i=0,...,n-1)
void dset(unsigned int n, const double *da, double *dy) {
	do {
		--n;
		dy[n] = *da;
	} while(n);
}