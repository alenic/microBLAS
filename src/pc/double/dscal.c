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

// y=da*y
void dscal(unsigned int n, double da, double *dy)
{
	unsigned int i;
	
	if(da == 1.0)
	{
		return;
	}
	
	if(da == 0.0)
	{
		for(i=0;i<n;i++) {
			dy[i]=0.0;
		}
		return;
	}
	
	for(i=0;i<n;i++) {
		dy[i]=da*dy[i];
	}
}