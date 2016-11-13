/*
            _                  ____  _        _    ____  
  _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
 | '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
 | | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
 |_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

 Author: Alessandro Nicolosi
 
---------------------------------------------------------

 

*/

#include "microBLAS.h"

// return x'*x
double dnorm2(unsigned int n, double *dx)
{
	long int i, m;
	register double dxdx, dxx1,dxx2,dxx3,dxx4;
	
	m=n-3;
	i=1;
	dxx1=dx[0];
	dxdx=dxx1*dxx1;
	while(i < m)
	{
		dxx1=dx[i];
		dxdx+=dxx1*dxx1;
		dxx2=dx[i+1];
		dxdx+=dxx2*dxx2;
		dxx3=dx[i+2];
		dxdx+=dxx3*dxx3;
		dxx4=dx[i+3];
		dxdx+=dxx4*dxx4;
		i+=4;
	}
	while(i < n)
	{
		dxdx+=dx[i]*dx[i];
		++i;
	}

	return dxdx;
}