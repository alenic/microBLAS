/*
            _                  ____  _        _    ____  
  _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
 | '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
 | | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
 |_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

 Author: Alessandro Nicolosi

---------------------------------------------------------

 Double precision subroutines of microBLAS library

*/

#ifndef DMICRO_BLAS_H
#define DMICRO_BLAS_H

#include <stdlib.h>

#ifdef __cpp
	extern "C" {
#endif

	// BLAS Level 1
	double *darray(unsigned int);
	double *dzeros(unsigned int);
	void dset(unsigned int, double *, const double *);
	void dcopy(unsigned int, double *, const double *);

	double ddot(unsigned int n, double *dx, double *dy);
	inline void daxpy (unsigned int n, double da, double *dx, double *dy);
	inline void daxpby(unsigned int n, double da, double *dx, double db, double *dy);
	void dscal(unsigned int n, double da, double *dy);
	void dvcal(unsigned int n, double da, double *dx, double *dy);
	double dsum(unsigned int n, double *dx);
	double dasum(unsigned int n, double *dx);
	void dswap(unsigned int n, double *dx, double *dy);
	double dnorm2(unsigned int n, double *dx);
	unsigned int dimin(unsigned int n, double *dx);
	unsigned int dimax(unsigned int n, double *dx);

	// BLAS Level 2
	void dgemv(unsigned int m, unsigned int n, double da, double *A, unsigned int lda, double *dx, double db, double *dy);

#ifdef __cpp
    }
#endif
#endif  // EF_BLAS_H
