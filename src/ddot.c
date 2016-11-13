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

double ddot(unsigned int n, double *dx, double *dy)
{
	unsigned int i, m;
	double dxdy;
	
	m = n-3;
	i = 1;
	
	dxdy=dx[0]*dy[0];
	while(i < m)
	{
		dxdy += dx[i]*dy[i];
		dxdy += dx[i+1]*dy[i+1];
		dxdy += dx[i+2]*dy[i+2];
		dxdy += dx[i+3]*dy[i+3];
		i += 4;
	}
	while(i < n)
	{
		dxdy += dx[i]*dy[i];
		++i;
	}

	return dxdy;
}