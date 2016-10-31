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

// y=da*A*x+beta*y
void dgemv(unsigned int m, unsigned int n, double da, double *A, unsigned int lda, double *dx, double db, double *dy)
{
	unsigned int i, j, jlda=0, jldai, mi;
	double wvar;

	mi = m-3;

	if(db != 0.0) {
		for(i=0; i<m; i++) dy[i] = db*dy[i];
	}
	
	for(j=0;j<n;j++)
	{
		wvar = dx[j]*da;
		i=0;

		while(i < mi) {
			jldai = jlda+i;                            
			dy[i]   += wvar*A[jldai]; 
			dy[i+1] += wvar*A[jldai+1]; 
			dy[i+2] += wvar*A[jldai+2];
			dy[i+3] += wvar*A[jldai+3];
			i+=4;                      
		}
		while(i < m) {
			dy[i] += wvar*A[jlda+i];
			++i;
		}
		jlda += lda;
  	}
}