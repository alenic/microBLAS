/*
            _                  ____  _        _    ____  
  _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
 | '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
 | | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
 |_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

 Author: Alessandro Nicolosi

---------------------------------------------------------

Include all precision subroutines of microBLAS library

*/

#ifndef MICRO_BLAS_H
#define MICRO_BLAS_H

#ifdef __cpp
	extern "C" {
#endif

	// BLAS Level 1
	double *darray(unsigned int);
	double *dzeros(unsigned int);
	void dset(unsigned int, const double *, double *);
	void dcopy(unsigned int, const double *, double *);
	void dswap(unsigned int n, double *, double *);

	double ddot(unsigned int n, const double *, const double *);
	double dnorm2(unsigned int n, const double *);
	double dsum(unsigned int n, const double *);
	double dasum(unsigned int n, const double *);
	unsigned int dmin(unsigned int n, const double *);
	unsigned int dmax(unsigned int n, const double *);
	unsigned int dimin(unsigned int n, const double *);
	unsigned int dimax(unsigned int n, const double *);



	void daxpy (unsigned int n, double da, double *dx, double *dy);
	void daxpby(unsigned int n, double da, double *dx, double db, double *dy);
	void dscal(unsigned int n, double da, double *dy);
	void dvcal(unsigned int n, double da, double *dx, double *dy);
	
	

	// BLAS Level 2
	void dgemv(unsigned int m, unsigned int n, double da, double *A, unsigned int lda, double *dx, double db, double *dy);

#ifdef __cpp
    }
#endif

#endif  // EF_BLAS_H
