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

// For dgemm cache
#define BLOCK_SIZE 64

#ifdef __cplusplus
    extern "C" {
#endif



// ============================ Vectors ================================

// allocate and return the pointer of the an empty vector (not initialized)
static inline RealType *vcreate_empty(unsigned int n) {
    RealType *ptr = (RealType *)malloc(n*sizeof(RealType));
    if (!ptr) return NULL;
    return ptr;
}

// allocate and return the pointer of the vector (0,0,...0)
static inline RealType *vcreate_zero(unsigned int n) {
    RealType *ptr = (RealType *)calloc(n, sizeof(RealType));
    if (!ptr) return NULL;
    return ptr;
}

// allocate and return the pointer of the the vector (a,a,...a)
static inline RealType *vcreate_const(unsigned int n, const RealType a) {
    RealType *vector = vcreate_empty(n);

    if (!vector) return NULL;

    for(unsigned int i = 0; i<n; i++)
        vector[i] = a;
    return vector;
}

// Free vector memory
static inline void vfree(RealType *v) {
    if(v != NULL)
        free(v);
}

// allocate and return the pointer of the the vector (min_range, min_range+1,...,max_range-1)
static inline RealType *vcreate_range(const RealType min_range, const RealType max_range) {
    if(min_range >= max_range) return NULL;

    unsigned int n = (unsigned int)(max_range - min_range);
    if (n == 0) return NULL;

    RealType *vector = vcreate_empty(n);
    if (!vector) return NULL;

    RealType value = min_range;

    for(unsigned int i = 0; i<n; i++)
        vector[i] = value++;

    return vector;
}

// y = (a,a,...,a)
static inline void vset_const(unsigned int n, const RealType a, RealType *y) {
    for(unsigned int i = 0; i<n; i++)
        y[i] = a;
}

// y = x
static inline void vcopy(unsigned int n, const RealType *x, RealType *y) {
    for(unsigned int i = 0; i<n; i++)
        y[i] = x[i];
}


// y = a*y
static inline void vscale(unsigned int n, const RealType a, RealType *y)
{
    if (a == 0.0) {
        for (unsigned int i = 0; i < n; i++)
            y[i] = 0.0;
        
        return;
    }
    if (a == 1.0) return;

    for (unsigned int i = 0; i < n; i++)
        y[i] *= a;
}

// y = x1 + x2
static inline void vxpx(unsigned int n, const RealType *x1, const RealType *x2, RealType *y)
{
    for(unsigned int i = 0; i<n; i++)
        y[i] += x1[i] + x2[i];
}

// y = a*x + y
static inline void vaxpy(unsigned int n, const RealType a, const RealType *x, RealType *y)
{
    if(a == 0.0) {
        return;
    }
    if(a == 1.0) {
        for(unsigned int i = 0; i<n; i++)
            y[i] += x[i];
    } else {
        for(unsigned int i = 0; i<n; i++)
            y[i] += a*x[i];
    }
}

// return the dot product <a, b>
static inline RealType dot(unsigned int n, const RealType *a, const RealType *b) {
    RealType sum = 0.0;
    unsigned int i = 0;

    // Process 4 elements per iteration
    for (; i + 4 <= n; i += 4) {
        sum += a[i] * b[i]
             + a[i+1] * b[i+1]
             + a[i+2] * b[i+2]
             + a[i+3] * b[i+3];
    }
    // Handle remainder
    for (; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

// return the sum of the components of the vector x
static inline RealType vsum(unsigned int n, const RealType *x) {
    RealType sum = 0.0;
    for(unsigned int i = 0; i<n; i++)
        sum += x[i];

    return sum;
}

// return the L2-squared norm of a vector x
static inline RealType l2_sq(unsigned int n, const RealType *x) {
    RealType sum = 0.0;

    for(unsigned int i = 0; i<n; i++)
        sum += x[i]*x[i];

    return sum;
}

// return the L2 norm of a vector x
static inline RealType l2(unsigned int n, const RealType *x) {
    return (RealType)sqrt(l2_sq(n, x));
}

// return the L2-squared norm of the vector x1-x2
static inline RealType l2_dist_sq(unsigned int n, const RealType *x1, const RealType *x2) {
    RealType sum = 0.0;
    RealType delta;
    for(unsigned int i = 0; i<n; i++) {
        delta = x1[i] - x2[i];
        sum += delta*delta;
    }

    return sum;
}

// return the L2 norm of the vector x1-x2
static inline RealType l2_dist(unsigned int n, const RealType *x1, const RealType *x2) {
    return (RealType)sqrt(l2_dist_sq(n, x1, x2));
}

// return the L1 norm of a vector x
static inline RealType l1(unsigned int n, const RealType *x) {
    RealType sum = 0.0;
    for(unsigned int i = 0; i<n; i++) {
        if(x[i] < 0)
            sum -= x[i];
        else
            sum += x[i];
    }

    return sum;
}

// return the minimum value of the vector x
static inline RealType vmin(unsigned int n, const RealType *x) {
    if (n == 0) return 0;

    RealType min_val;
    min_val = x[0];
    for(unsigned int i = 1; i<n; i++) {
        if(x[i] < min_val) {
            min_val = x[i];
        }
    }

    return min_val;
}

// return the maximum value of the vector x
static inline RealType vmax(unsigned int n, const RealType *x) {
    if (n == 0) return 0;

    RealType max_val;
    max_val = x[0];
    for(unsigned int i = 1; i<n; i++) {
        if(x[i] > max_val) {
            max_val = x[i];
        }
    }

    return max_val;
}

// return the index of the minimum value of the vector x
static inline unsigned int vimin(unsigned int n, const RealType *x) {
    if (n == 0) return 0;

    unsigned int min_index;
    RealType min_val;
    min_index = 0;

    min_val = x[0];
    for(unsigned int i = 1; i<n; i++) {
        if(x[i] < min_val) {
            min_val = x[i];
            min_index = i;
        }
    }

    return min_index;
}

// return the index of the maximum value of the vector x
static inline unsigned int vimax(unsigned int n, const RealType *x) {
    if (n == 0) return 0;

    unsigned int max_index;
    RealType max_val;
    max_index = 0;

    max_val = x[0];
    for(unsigned int i = 1; i<n; i++) {
        if(x[i] > max_val) {
            max_val = x[i];
            max_index = i;
        }
    }
    return max_index;
}

// ============================ Matrix ================================

// allocate and return the pointer of the an empty vector (not initialized)
static inline RealType *mcreate_empty(unsigned int rows, unsigned int cols) {
    RealType *ptr = (RealType *)malloc(rows*cols*sizeof(RealType));
    if (!ptr) return NULL;
    return ptr;
}

// allocate and return the pointer of the vector (0,0,...,0)
static inline RealType *mcreate_zero(unsigned int rows, unsigned int cols) {
    RealType *ptr = (RealType *)calloc(rows*cols, sizeof(RealType));
    if (!ptr) return NULL;
    return ptr;
}

// allocate and return the pointer of the the vector (a,a,...,a)
static inline RealType *mcreate_const(unsigned int rows, unsigned int cols, const RealType a) {
    RealType *matrix = mcreate_empty(rows, cols);
    if (!matrix) return NULL;

    unsigned int n = rows*cols;

    for(unsigned int i = 0; i<n; i++)
        matrix[i] = a;


    return matrix;
}

// Free matrix memory
static inline void mfree(RealType *m) {
    if(m != NULL)
        free(m);
}

// general cumulative matrix-vector multiplication: y = A*x + b*y (WARNING it doesn't check len(x) == cols)
static inline void gemv(unsigned int rows, unsigned int cols, const RealType *A, const RealType *x, RealType b, RealType *y)
{
    unsigned int ilda=0;
    for(unsigned int i=0; i<rows; i++) {
        RealType sum = (b == 0.0 ? 0.0 : (b == 1.0 ? y[i] : b*y[i]));
        for(unsigned int j=0; j<cols; j++) {
            sum += A[ilda+j]*x[j];
        }
        y[i] = sum;
        ilda += cols;
    }
}


// General matrix-matrix multiplication with accumulation
// Y = X1 * X2 + b * Y
// X1: (rows_x1, cols_x1)
// X2: (cols_x1, cols_x2)
// Y:  (rows_x1, cols_x2)
static inline void gemm(unsigned int rows_x1, unsigned int cols_x1, unsigned int cols_x2,
                        const RealType *X1, const RealType *X2, RealType *Y, RealType b) {

    for (unsigned int ii = 0; ii < rows_x1; ii += BLOCK_SIZE) {
        for (unsigned int jj = 0; jj < cols_x2; jj += BLOCK_SIZE) {
            for (unsigned int kk = 0; kk < cols_x1; kk += BLOCK_SIZE) {

                unsigned int i_max = (ii + BLOCK_SIZE < rows_x1) ? ii + BLOCK_SIZE : rows_x1;
                unsigned int j_max = (jj + BLOCK_SIZE < cols_x2) ? jj + BLOCK_SIZE : cols_x2;
                unsigned int k_max = (kk + BLOCK_SIZE < cols_x1) ? kk + BLOCK_SIZE : cols_x1;

                for (unsigned int i = ii; i < i_max; i++) {
                    for (unsigned int j = jj; j < j_max; j++) {
                        RealType sum = (kk == 0)
                            ? ( (b == 0.0) ? 0.0 : (b == 1.0 ? Y[i*cols_x2 + j] : b*Y[i*cols_x2 + j]) )
                            : Y[i*cols_x2 + j];

                        for (unsigned int k = kk; k < k_max; k++) {
                            sum += X1[i*cols_x1 + k] * X2[k*cols_x2 + j];
                        }
                        Y[i*cols_x2 + j] = sum;
                    }
                }
            }
        }
    }
}





#ifdef __cplusplus
    }
#endif

#endif  // MICRO_BLAS_H
