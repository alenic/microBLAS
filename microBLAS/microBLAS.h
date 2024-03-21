/*
            _                  ____  _        _    ____  
  _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
 | '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
 | | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
 |_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

 Author: Alessandro Nicolosi
*/

#ifndef MICRO_BLAS_H
#define MICRO_BLAS_H
#include <stdlib.h>
#include <math.h>

#ifdef REAL_TYPE_DOUBLE
    typedef double RealType;
#else
    typedef float RealType;
#endif


#ifdef __cplusplus
    extern "C" {
#endif

// ============================ Vectors ================================
RealType *vcreate_empty(unsigned int n);
RealType *vcreate_zero(unsigned int n);
RealType *vcreate_const(unsigned int n, const RealType a);
RealType *vcreate_range(const RealType min_range, const RealType max_range);
void vset_const(unsigned int n, const RealType a, RealType *y);
void vcopy(unsigned int n, const RealType *x, RealType *y);
void vscale(unsigned int n, const RealType a, RealType *y);
void vxpx(unsigned int n, const RealType *x1, const RealType *x2, RealType *y);
void vaxpy(unsigned int n, const RealType a, const RealType *x, RealType *y);
RealType dot(unsigned int n, const RealType *a, const RealType *b);
RealType vsum(unsigned int n, const RealType *x);
RealType l2_sq(unsigned int n, const RealType *x);
RealType l2(unsigned int n, const RealType *x);
RealType l2_dist_sq(unsigned int n, const RealType *x1, const RealType *x2);
RealType l2_dist(unsigned int n, const RealType *x1, const RealType *x2);
RealType l1(unsigned int n, const double *x);
RealType vmin(unsigned int n, const RealType *x);
RealType vmax(unsigned int n, const RealType *x);
unsigned int vimin(unsigned int n, const RealType *x);
unsigned int vimax(unsigned int n, const RealType *x);

// ============================ Matrix ================================
RealType *mcreate_empty(unsigned int rows, unsigned int cols);
RealType *mcreate_zero(unsigned int rows, unsigned int cols);
RealType *mcreate_const(unsigned int rows, unsigned int cols, const RealType a);

void gemv(unsigned int rows, unsigned int cols, const RealType *A, const RealType *x, RealType b, RealType *y);
void gemm(unsigned int rows_x1,
          unsigned int cols_x1,
          unsigned int cols_x2,
          const RealType *X1,
          const RealType *X2,
          RealType *Y
);

#ifdef __cplusplus
    }
#endif

#endif  // MICRO_BLAS_H
