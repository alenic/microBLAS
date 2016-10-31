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

void daxpy (unsigned int n, double da, double *dx, double *dy)
{
	long int i, m;
	register double rda = da;
	
	if(rda == 1.0)
	{
		m=n-3;
		i=0;
//-----------------> perform operations with loop unrolling
		while(i < m)
		{
			dy[i]   += dx[i];
			dy[i+1] += dx[i+1];
			dy[i+2] += dx[i+2];
			dy[i+3] += dx[i+3];
			i += 4;
		}
//-----------------> perform operations to the rest of array 
		while(i < n)
		{
			dy[i] += dx[i];
			++i;
		}
		return;
	}
	
	if(rda != 0.0)
	{
		m=n-3;
		i=0;
//-----------------> perform operations with loop unrolling
		while(i < m)
		{
			dy[i]   += rda*dx[i];
			dy[i+1] += rda*dx[i+1];
			dy[i+2] += rda*dx[i+2];
			dy[i+3] += rda*dx[i+3];
			i += 4;
		}
//-----------------> perform operations to the rest of array 
		while(i < n)
		{
			dy[i] += rda*dx[i];
			++i;
		}
	}
}