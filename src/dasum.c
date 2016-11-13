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

double dasum(unsigned int n, double *dx)
{
	unsigned int i;
	double sum = 0.0;
	
	for(i=0; i<n; i++)
	{
		if(dx[i] < 0)
			sum = sum - dx[i];
		else
			sum = sum + dx[i];
	}
	return sum;
}