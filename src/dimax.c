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

unsigned int dimax(unsigned int n, double *dx)
{
	unsigned int i,i_max;
	register double max=dx[0],dxx;
	
	for(i=1;i<n;i++)
	{
		dxx=dx[i];
		if(dxx>max)
		{
			max=dxx;
			i_max=i;
		}
	}

	return i_max;
}