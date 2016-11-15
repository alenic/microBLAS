/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"
// Swap the values of two vectors:  x1 <-> x2
void dswap(unsigned int n, double *dx1, double *dx2)
{
    double c;
	do {
		--n;
		c=dx1[n];
		dx1[n]=dx2[n];
		dx2[n]=c;
	} while(n);
}