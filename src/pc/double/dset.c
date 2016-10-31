/*
            _                  ____  _        _    ____  
  _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
 | '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
 | | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
 |_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

 Author: Alessandro Nicolosi
 
---------------------------------------------------------

 

*/

#include "dmicroBLAS.h"

// Set a vector to a constant value
void dset(unsigned int n, double *dx, const double *da)
{
	int i;
	for(i=0; i<n; i++) {
		dx[i] = *da;
	}
}