/*
            _                  ____  _        _    ____  
  _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
 | '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
 | | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
 |_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 

author: Alessandro Nicolosi
website: https://github.com/alenic/microBLAS
license: MIT
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
#ifndef BLOCK_SIZE
    #define BLOCK_SIZE 64
#endif

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
    else if(a == 1.0) {
        for(unsigned int i = 0; i<n; i++)
            y[i] += x[i];
    }
    else if(a == -1.0) {
        for(unsigned int i = 0; i<n; i++)
            y[i] -= x[i];
    } else {
        for(unsigned int i = 0; i<n; i++)
            y[i] += a*x[i];
    }
}

// return the sum of the components of the vector x
static inline RealType vsum(unsigned int n, const RealType *x) {
    RealType sum = 0.0;
    for(unsigned int i = 0; i<n; i++)
        sum += x[i];

    return sum;
}

// Return the elementwise multiply: y = x1 * x2
static inline void vmul(unsigned int n, const RealType *x1, const RealType *x2, RealType *y) {
    for (unsigned int i = 0; i < n; i++)
        y[i] = x1[i] * x2[i];
}

// Return the elementwise divide: y = x1 / x2
static inline void vdiv(unsigned int n, const RealType *x1, const RealType *x2, RealType *y) {
    for (unsigned int i = 0; i < n; i++)
        y[i] = x1[i] / x2[i];
}


// return the dot product: <a, b>
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


// return the L2-squared norm of a vector x
static inline RealType l2sq(unsigned int n, const RealType *x) {
    RealType sum = 0.0;

    for(unsigned int i = 0; i<n; i++)
        sum += x[i]*x[i];

    return sum;
}

// return the L2 norm of a vector x
static inline RealType l2(unsigned int n, const RealType *x) {
    return (RealType)sqrt(l2sq(n, x));
}

// return the L2-squared norm of the vector x1-x2
static inline RealType l2distsq(unsigned int n, const RealType *x1, const RealType *x2) {
    RealType sum = 0.0;
    RealType delta;
    for(unsigned int i = 0; i<n; i++) {
        delta = x1[i] - x2[i];
        sum += delta*delta;
    }

    return sum;
}

// return the L2 norm of the vector x1-x2
static inline RealType l2dist(unsigned int n, const RealType *x1, const RealType *x2) {
    return (RealType)sqrt(l2distsq(n, x1, x2));
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

// return the L-inf norm of a vector x
static inline RealType linf(unsigned int n, const RealType *x) {
    if (n == 0) return 0;
    RealType max_val = fabs(x[0]);
    for (unsigned int i = 1; i < n; i++) {
        RealType val = fabs(x[i]);
        if (val > max_val) max_val = val;
    }
    return max_val;
}

// return the L-inf norm of a vector x
static inline RealType vamax(unsigned int n, const RealType *x) {
    return linf(n, x);
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

// return the index of the maximum absolute value of the vector x
static inline unsigned int viamax(unsigned int n, const RealType *x) {
    if (n == 0) return 0;

    unsigned int idx = 0;
    RealType max_val = fabs(x[0]);
    for (unsigned int i = 1; i < n; i++) {
        RealType val = fabs(x[i]);
        if (val > max_val) {
            max_val = val;
            idx = i;
        }
    }
    return idx;
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

// Transpose the matrix A: AT = A^T
static inline void mtranspose(unsigned int rows, unsigned int cols,
                              const RealType *A, RealType *AT) {
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            AT[j*rows + i] = A[i*cols + j];
        }
    }
}

// C = A + B
static inline void madd(unsigned int rows, unsigned int cols,
                        const RealType *A, const RealType *B, RealType *C) {
    unsigned int n = rows * cols;
    for (unsigned int i = 0; i < n; i++)
        C[i] = A[i] + B[i];
}


// Y = alpha*Y
static inline void mscale(unsigned int rows, unsigned int cols,
                          RealType alpha, RealType *Y) {

    unsigned int n = rows * cols;
    for (unsigned int i = 0; i < n; i++)
        Y[i] *= alpha;
}

// General cumulative matrix-vector multiplication: y = A*x + alpha*y (WARNING it doesn't check len(x) == cols)
static inline void gemv(unsigned int rows, unsigned int cols, const RealType *A, const RealType *x, RealType alpha, RealType *y)
{
    unsigned int ilda=0;
    for(unsigned int i=0; i<rows; i++) {
        RealType sum = (alpha == 0.0 ? 0.0 : (alpha == 1.0 ? y[i] : alpha*y[i]));

        for(unsigned int j=0; j<cols; j++) {
            sum += A[ilda+j]*x[j];
        }

        y[i] = sum;
        ilda += cols;
    }
}


// General matrix-matrix multiplication with accumulation
// C = A * B + alpha * C
// A: (rows_a, cols_a)
// B: (cols_a, cols_b)
// C:  (rows_a, cols_b)
static inline void gemm(unsigned int rows_a, unsigned int cols_a, unsigned int cols_b,
                        const RealType *A, const RealType *B, RealType alpha, RealType *C) {

    for (unsigned int ii = 0; ii < rows_a; ii += BLOCK_SIZE) {
        for (unsigned int jj = 0; jj < cols_b; jj += BLOCK_SIZE) {
            for (unsigned int kk = 0; kk < cols_a; kk += BLOCK_SIZE) {

                unsigned int i_max = (ii + BLOCK_SIZE < rows_a) ? ii + BLOCK_SIZE : rows_a;
                unsigned int j_max = (jj + BLOCK_SIZE < cols_b) ? jj + BLOCK_SIZE : cols_b;
                unsigned int k_max = (kk + BLOCK_SIZE < cols_a) ? kk + BLOCK_SIZE : cols_a;

                for (unsigned int i = ii; i < i_max; i++) {
                    for (unsigned int j = jj; j < j_max; j++) {
                        RealType sum;

                        if (kk == 0) {
                            // First block: scale C
                            if (alpha == 0.0) sum = 0.0;
                            else if (alpha == 1.0) sum = C[i*cols_b + j];
                            else sum = alpha * C[i*cols_b + j];
                        } else {
                            // Later blocks: keep accumulating
                            sum = C[i*cols_b + j];
                        }

                        for (unsigned int k = kk; k < k_max; k++) {
                            sum += A[i*cols_a + k] * B[k*cols_b + j];
                        }

                        C[i*cols_b + j] = sum;
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
