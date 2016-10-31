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
// dx <-> dy
void dswap(unsigned int n, double *dx, double *dy)
{
	unsigned int i;
	register double c;
	
	for(i=0;i<n;i++)
	{
		c=dx[i];
		dx[i]=dy[i];
		dy[i]=c;
	}
}