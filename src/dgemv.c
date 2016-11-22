/*
           _                  ____  _        _    ____  
 _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
| '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
| | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
|_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

Author: Alessandro Nicolosi

*/
#include "microBLAS.h"

// Add the matrix-vector product: y=A*x + beta*y
void dgemv(unsigned int m, unsigned int n, unsigned int lda, const double *A, const double *dx, const double db, double *dy)
{
	unsigned int i, j, ilda=0;

	dscal(n, db, dy);
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
			dy[i] += A[ilda+j]*dx[j];
		}
		ilda += lda;
	}
}