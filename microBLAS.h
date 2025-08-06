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


// Select real type and corresponding math functions
#ifdef REAL_TYPE_DOUBLE
    typedef double RealType;
    #define REAL_SQRT(x) sqrt(x)
    #define REAL_ABS(x) fabs(x)
#else
    typedef float RealType;
    #define REAL_SQRT(x) sqrtf(x)
    #define REAL_ABS(x) fabsf(x)
#endif

// For dgemm cache
#ifndef BLOCK_SIZE
    #define BLOCK_SIZE 64
#endif

#ifdef __cplusplus
    extern "C" {
#endif

// This is a vector
typedef struct {
    RealType *data;
    size_t n;
} Vector;

// This is a matrix
typedef struct {
    RealType *data;
    size_t rows;
    size_t cols;
} Matrix;

typedef enum {
    MB_SUCCESS = 0,     // success
    MB_ERR_ALLOC,       // memory allocation failed
    MB_ERR_DIM_MISMATCH,// invalid dimensions
    MB_ERR_NULL_PTR,    // null pointer passed
    MB_ERR_DIV_BY_ZERO,    // division by 0
    MB_ERR_UNKNOWN      // fallback error
} MBError;

// ============================ Vectors ================================

// helper function to valid a Vector
static inline MBError vvalid(const Vector *a) {
    if (a == NULL)                // Null pointer for the vector itself
        return MB_ERR_NULL_PTR;
    if (a->n > 0 && a->data == NULL) // Non-zero length but no data buffer
        return MB_ERR_ALLOC;
    return MB_SUCCESS;
}

// check that a and b are same length
static inline MBError vvalid2(const Vector *a, const Vector *b) {
    MBError err;
    if ((err = vvalid(a)) != MB_SUCCESS) return err;
    if ((err = vvalid(b)) != MB_SUCCESS) return err;
    if (a->n != b->n)   return MB_ERR_DIM_MISMATCH;
    return MB_SUCCESS;
}

// check a, b and destination y all same length
static inline MBError vvalid3(const Vector *y, const Vector *a, const Vector *b) {
    MBError err;
    if ((err = vvalid(y)) != MB_SUCCESS) return err;
    if (y->n != a->n) return MB_ERR_DIM_MISMATCH;
    if ((err = vvalid2(a, b)) != MB_SUCCESS) return err;
    return MB_SUCCESS;
}

// allocate an empty vector (not initialized)
static inline MBError vcreate_empty(Vector *v, size_t n) {
    if (v == NULL) return MB_ERR_NULL_PTR;
    v->n = n;

    if (n > 0) {
        v->data = malloc(n * sizeof *v->data);
        if (!v->data) return MB_ERR_ALLOC;
    } else {
        v->data = NULL;
    }
    return MB_SUCCESS;
}

// allocate a zero vector (0,0,...0)
static inline MBError vcreate_zero(Vector *v, size_t n) {
    if (v == NULL) return MB_ERR_NULL_PTR;
    v->n = n;

    if (n > 0) {
        v->data = calloc(n, sizeof *v->data);
        if (!v->data) return MB_ERR_ALLOC;
    } else {
        v->data = NULL;
    }
    return MB_SUCCESS;
}

// allocate a const vector of size n: (value, value,...,value)
static inline MBError vcreate_const(Vector *v, size_t n, RealType value) {
    if (v == NULL) return MB_ERR_NULL_PTR;
    v->n = n;
    if (n == 0) {
        v->data = NULL;
        return MB_SUCCESS;
    }
    if (value == (RealType)0) {
        v->data = calloc(n, sizeof *v->data);
        if (!v->data) return MB_ERR_ALLOC;
    } else {
        v->data = malloc(n * sizeof *v->data);
        if (!v->data) return MB_ERR_ALLOC;

        for (size_t i = 0; i < n; i++)
            v->data[i] = value;
    }
    return MB_SUCCESS;
}

// free vector memory
static inline MBError vfree(Vector *v) {
    MBError err = vvalid(v);
    if (err != MB_SUCCESS) return err;
    free(v->data);
    v->data = NULL;
    v->n = 0;
    return MB_SUCCESS;
}

// set all the elements of a vector to a constant alpha:  y = (alpha, alpha,...,alpha)
static inline MBError vset_const(Vector *y, const RealType alpha) {
    MBError err = vvalid(y);
    if (err != MB_SUCCESS) return err;

    for(size_t i = 0; i < y->n; i++)
        y->data[i] = alpha;

    return MB_SUCCESS;
}

// y = a
static inline MBError vcopy(Vector *y, const Vector *a) {
    MBError err = vvalid2(y, a);
    if (err != MB_SUCCESS) return err;

    for (size_t i = 0; i < y->n; i++)
        y->data[i] = a->data[i];
    return MB_SUCCESS;
}
// y = alpha*y
static inline MBError vscale(Vector *y, const RealType alpha) {
    MBError err = vvalid(y);
    if (err != MB_SUCCESS) return err;

    if (alpha == 0.0) {
        for (size_t i = 0; i < y->n; i++)
            y->data[i] = 0.0;
    } else if (alpha != 1.0) {
        for (size_t i = 0; i < y->n; i++)
            y->data[i] *= alpha;
    }
    return MB_SUCCESS;
}

// y = a + b
static inline MBError vadd(Vector *y, const Vector *a, const Vector *b)
{
    MBError err = vvalid3(y, a, b);
    if (err != MB_SUCCESS) return err;

    for(size_t i = 0; i<y->n; i++)
        y->data[i] = a->data[i] + b->data[i];
    
    return MB_SUCCESS;
}

// y = alpha*a + y
static inline MBError vaxpy(Vector *y, const RealType alpha, const Vector *a)
{
    MBError err = vvalid2(y, a);
    if (err != MB_SUCCESS) return err;

    if(alpha == 0.0) {
        return MB_SUCCESS;
    } else if(alpha == 1.0) {
        for(size_t i = 0; i<y->n; i++)
            y->data[i] += a->data[i];
    } else if(alpha == -1.0) {
        for(size_t i = 0; i<y->n; i++)
            y->data[i] -= a->data[i];
    } else {
        for(size_t i = 0; i<y->n; i++)
            y->data[i] += alpha*a->data[i];
    }

    return MB_SUCCESS;
}

// return the sum of the components of the vector a
static inline MBError vsum(RealType *out, const Vector *a) {
    MBError err = vvalid(a);
    if (err != MB_SUCCESS) return err;

    RealType sum = 0.0;
    for(size_t i = 0; i<a->n; i++)
        sum += a->data[i];

    *out = sum;
    return MB_SUCCESS;
}

// return the elementwise multiply: y = a * b
static inline MBError vmul(Vector *y, const Vector *a, const Vector *b) {
    MBError err = vvalid3(y, a, b);
    if (err != MB_SUCCESS) return err;

    for (size_t i = 0; i < y->n; i++)
        y->data[i] = a->data[i] * b->data[i];
    
    return MB_SUCCESS;
}

// return the elementwise divide: y = x1 / x2
static inline MBError vdiv(Vector *y, const Vector *a, const Vector *b) {
    MBError err = vvalid3(y, a, b);
    if (err != MB_SUCCESS) return err;

    for (size_t i = 0; i < y->n; i++) {
        if(b->data[i] == 0.0) {
            return MB_ERR_DIV_BY_ZERO;
        }
        y->data[i] = a->data[i] / b->data[i];
    }
        
    return MB_SUCCESS;
}


// return the dot product: out = <a, b>
static inline MBError vdot(RealType *out, const Vector *a, const Vector *b) {
    MBError err = vvalid2(a, b);
    if (err != MB_SUCCESS) return err;

    RealType sum = 0.0;
    size_t i = 0;

    for (; i + 4 <= a->n; i += 4) {
        sum += a->data[i] * b->data[i]
             + a->data[i+1] * b->data[i+1]
             + a->data[i+2] * b->data[i+2]
             + a->data[i+3] * b->data[i+3];
    }
    for (; i < a->n; i++) {
        sum += a->data[i] * b->data[i];
    }
    *out = sum;

    return MB_SUCCESS;
}


// return the L2-squared norm of the vector a: ||a||^2
static inline MBError vl2sq(RealType *out, const Vector *a) {
    MBError err = vvalid(a);
    if (err != MB_SUCCESS) return err;

    RealType sum = 0.0;

    for(size_t i = 0; i<a->n; i++)
        sum += a->data[i] * a->data[i];

    *out = sum;

    return MB_SUCCESS;
}

// return the L2 norm of the vector a: ||a||
static inline MBError vl2(RealType *out, const Vector *a) {
    MBError err = vl2sq(out, a);
    if (err != MB_SUCCESS) return err;

    *out = (RealType)sqrt(*out);

    return MB_SUCCESS;
}

// return the L2-squared norm of the vector a-b: ||a-b||^2
static inline MBError vl2distsq(RealType *out, const Vector *a, const Vector *b) {
    MBError err = vvalid2(a, b);
    if (err != MB_SUCCESS) return err;

    RealType sum = 0.0;
    RealType delta;

    for(size_t i = 0; i<a->n; i++) {
        delta = a->data[i] - b->data[i];
        sum += delta * delta;
    }

    *out = sum;
    return MB_SUCCESS;
}

// return the L2 norm of the vector a-b: ||a-b||
static inline MBError vl2dist(RealType *out, const Vector *a, const Vector *b) {
    MBError err = vl2distsq(out, a, b);
    if (err != MB_SUCCESS) return err;

    *out = (RealType)sqrt(*out);

    return MB_SUCCESS;
}

// return the L1 norm of the vector a: |a|
static inline MBError vl1(RealType *out, const Vector *a) {
    MBError err = vvalid(a);
    if (err != MB_SUCCESS) return err;

    RealType sum = 0.0;
    for(size_t i = 0; i<a->n; i++) {
        if(a->data[i] < 0)
            sum -= a->data[i];
        else
            sum += a->data[i];
    }

    *out = sum;

    return MB_SUCCESS;
}

// return the L-inf norm of the vector a: |a|_inf
static inline MBError vlinf(RealType *out, const Vector *a) {
    MBError err = vvalid(a);
    if (err != MB_SUCCESS) return err;
    if (a->n == 0) return MB_ERR_DIM_MISMATCH;

    RealType max_val = (RealType)REAL_ABS(a->data[0]);
    for (size_t i = 1; i < a->n; i++) {
        RealType val = (RealType)REAL_ABS(a->data[i]);
        if (val > max_val)
            max_val = val;
    }

    *out = max_val;

    return MB_SUCCESS;
}

// return the minimum value of the vector x
static inline MBError vmin(RealType *out, const Vector *a) {
    MBError err = vvalid(a);
    if (err != MB_SUCCESS) return err;
    if (a->n == 0) return MB_ERR_DIM_MISMATCH;

    RealType min_val;
    min_val = a->data[0];
    for(size_t i = 1; i<a->n; i++) {
        if(a->data[i] < min_val) {
            min_val = a->data[i];
        }
    }
    *out = min_val;

    return MB_SUCCESS;
}

// return the maximum value of the vector x
static inline MBError vmax(RealType *out, const Vector *a) {
    MBError err = vvalid(a);
    if (err != MB_SUCCESS) return err;
    if (a->n == 0) return MB_ERR_DIM_MISMATCH;

    RealType max_val;
    max_val = a->data[0];
    for(size_t i = 1; i<a->n; i++) {
        if(a->data[i] > max_val) {
            max_val = a->data[i];
        }
    }

    *out = max_val;

    return MB_SUCCESS;
}

// return the max of abs values of the vector a
static inline MBError vamax(RealType *out, const Vector *a) {
    MBError err = vlinf(out, a);
    if (err != MB_SUCCESS) return err;

    return MB_SUCCESS;
}


// return the index of the minimum value of the vector a
static inline MBError vimin(size_t *out, const Vector *a) {
    MBError err = vvalid(a);
    if (err != MB_SUCCESS) return err;
    if (a->n == 0) return MB_ERR_DIM_MISMATCH;

    size_t min_index;
    RealType min_val;
    min_index = 0;

    min_val = a->data[0];
    for(size_t i = 1; i<a->n; i++) {
        if(a->data[i] < min_val) {
            min_val = a->data[i];
            min_index = i;
        }
    }

    *out = min_index;

    return MB_SUCCESS;
}

// return the index of the maximum value of the vector a
static inline MBError vimax(size_t *out, const Vector *a) {
    MBError err = vvalid(a);
    if (err != MB_SUCCESS) return err;
    if (a->n == 0) return MB_ERR_DIM_MISMATCH;

    size_t max_index = 0;
    RealType max_val = a->data[0];

    for(size_t i = 1; i<a->n; i++) {
        if(a->data[i] > max_val) {
            max_val = a->data[i];
            max_index = i;
        }
    }

    *out = max_index;

    return MB_SUCCESS;
}

// return the index of the maximum absolute value of the vector a
static inline MBError viamax(size_t *out, const Vector *a) {
    MBError err = vvalid(a);
    if (err != MB_SUCCESS) return err;
    if (a->n == 0) return MB_ERR_DIM_MISMATCH;

    size_t max_index = 0;
    RealType max_val = (RealType)REAL_ABS(a->data[0]);

    for (size_t i = 1; i < a->n; i++) {
        RealType val = (RealType)REAL_ABS(a->data[i]);
        if (val > max_val) {
            max_val = val;
            max_index = i;
        }
    }

    *out = max_index;

    return MB_SUCCESS;
}

// ====================== Matrix ==============================

static inline MBError mvalid(const Matrix *m) {
    if (m == NULL) return MB_ERR_NULL_PTR;
    if (m->rows * m->cols > 0 && m->data == NULL) return MB_ERR_ALLOC;
    return MB_SUCCESS;
}

// check two matrices have same dimensions
static inline MBError mvalid2(const Matrix *a, const Matrix *b) {
    MBError err;
    if ((err = mvalid(a)) != MB_SUCCESS) return err;
    if ((err = mvalid(b)) != MB_SUCCESS) return err;
    if (a->rows != b->rows || a->cols != b->cols)
        return MB_ERR_DIM_MISMATCH;
    return MB_SUCCESS;
}

// check y, a, b all same dimensions
static inline MBError mvalid3(const Matrix *y, const Matrix *a, const Matrix *b) {
    MBError err;
    if ((err = mvalid(y)) != MB_SUCCESS) return err;
    if (y->rows != a->rows || y->cols != a->cols)
        return MB_ERR_DIM_MISMATCH;
    if ((err = mvalid2(a,b)) != MB_SUCCESS) return err;
    return MB_SUCCESS;
}

// allocate an empty matrix
static inline MBError mcreate_empty(Matrix *m, size_t rows, size_t cols) {
    if (m == NULL) return MB_ERR_NULL_PTR;
    m->rows = rows; m->cols = cols;
    size_t sz = rows*cols;
    if (sz > 0) {
        m->data = malloc(sz * sizeof *m->data);
        if (!m->data) return MB_ERR_ALLOC;
    } else {
        m->data = NULL;
    }
    return MB_SUCCESS;
}

// allocate a zero matrix
static inline MBError mcreate_zero(Matrix *m, size_t rows, size_t cols) {
    if (m == NULL) return MB_ERR_NULL_PTR;
    m->rows = rows; m->cols = cols;
    size_t sz = rows*cols;
    if (sz > 0) {
        m->data = calloc(sz, sizeof *m->data);
        if (!m->data) return MB_ERR_ALLOC;
    } else {
        m->data = NULL;
    }
    return MB_SUCCESS;
}

// allocate a const matrix
static inline MBError mcreate_const(Matrix *m, size_t rows, size_t cols, RealType a) {
    MBError err = mcreate_empty(m, rows, cols);
    if (err != MB_SUCCESS) return err;
    size_t n = rows*cols;
    for (size_t i = 0; i < n; i++)
        m->data[i] = a;
    return MB_SUCCESS;
}

// free matrix memory
static inline MBError mfree(Matrix *m) {
    MBError err = mvalid(m);
    if (err != MB_SUCCESS) return err;
    free(m->data);
    m->data = NULL;
    m->rows = m->cols = 0;
    return MB_SUCCESS;
}

// Transpose: Y = A^T
static inline MBError mtranspose(Matrix *Y, const Matrix *A) {
    MBError err;
    if ((err = mvalid(A)) != MB_SUCCESS) return err;
    if ((err = mvalid(Y)) != MB_SUCCESS) return err;
    if (Y->rows != A->cols || Y->cols != A->rows)
        return MB_ERR_DIM_MISMATCH;
    for (size_t i = 0; i < A->rows; i++)
        for (size_t j = 0; j < A->cols; j++)
            Y->data[j*A->rows + i] = A->data[i*A->cols + j];
    return MB_SUCCESS;
}

// C = A + B
static inline MBError madd(Matrix *C, const Matrix *A, const Matrix *B) {
    MBError err = mvalid3(C, A, B);
    if (err != MB_SUCCESS) return err;
    size_t n = A->rows * A->cols;
    for (size_t i = 0; i < n; i++)
        C->data[i] = A->data[i] + B->data[i];
    return MB_SUCCESS;
}

// Y = A + diag(d1,..,dn)
static inline MBError madddiag(Matrix *Y, const Matrix *A, const Vector *diag) {
    MBError err;
    if ((err = mvalid(A)) != MB_SUCCESS) return err;
    if ((err = vvalid(diag)) != MB_SUCCESS) return err;
    if (A->rows != A->cols || diag->n != A->rows) return MB_ERR_DIM_MISMATCH;
    if ((err = mvalid(Y)) != MB_SUCCESS) return err;
    if (Y->rows != A->rows || Y->cols != A->cols) return MB_ERR_DIM_MISMATCH;
    size_t n = A->rows, stride = n+1;
    for (size_t i = 0; i < n; i++)
        Y->data[i*stride] = A->data[i*stride] + diag->data[i];
    return MB_SUCCESS;
}

// Y = alpha * Y
static inline MBError mscale(Matrix *Y, RealType alpha) {
    MBError err = mvalid(Y);
    if (err != MB_SUCCESS) return err;
    size_t n = Y->rows * Y->cols;
    for (size_t i = 0; i < n; i++)
        Y->data[i] *= alpha;
    return MB_SUCCESS;
}

// y = A*x + alpha*y
static inline MBError gemv(Vector *y, const Matrix *A, const Vector *x, RealType alpha) {
    MBError err;
    if ((err = mvalid(A)) != MB_SUCCESS) return err;
    if ((err = vvalid(x)) != MB_SUCCESS) return err;
    if ((err = vvalid(y)) != MB_SUCCESS) return err;
    if (A->cols != x->n || A->rows != y->n) return MB_ERR_DIM_MISMATCH;
    size_t idx = 0;
    for (size_t i = 0; i < A->rows; i++, idx += A->cols) {
        RealType sum = (alpha == 0.0 ? 0.0
                         : (alpha == 1.0 ? y->data[i]
                                        : alpha*y->data[i]));
        for (size_t j = 0; j < A->cols; j++)
            sum += A->data[idx+j] * x->data[j];
        y->data[i] = sum;
    }
    return MB_SUCCESS;
}

// C = A*B + alpha*C
static inline MBError gemm(Matrix *C, const Matrix *A, const Matrix *B, RealType alpha) {
    MBError err;
    if ((err = mvalid(A)) != MB_SUCCESS) return err;
    if ((err = mvalid(B)) != MB_SUCCESS) return err;
    if ((err = mvalid(C)) != MB_SUCCESS) return err;
    if (A->cols != B->rows || A->rows != C->rows || B->cols != C->cols)
        return MB_ERR_DIM_MISMATCH;

    for (size_t ii = 0; ii < A->rows; ii += BLOCK_SIZE) {
        for (size_t jj = 0; jj < B->cols; jj += BLOCK_SIZE) {
            for (size_t kk = 0; kk < A->cols; kk += BLOCK_SIZE) {
                
                size_t i_max = ii + BLOCK_SIZE < A->rows ? ii+BLOCK_SIZE : A->rows;
                size_t j_max = jj + BLOCK_SIZE < B->cols ? jj+BLOCK_SIZE : B->cols;
                size_t k_max = kk + BLOCK_SIZE < A->cols ? kk+BLOCK_SIZE : A->cols;
                
                for (size_t i = ii; i < i_max; i++) {
                    for (size_t j = jj; j < j_max; j++) {
                        RealType sum;
                        if (kk == 0) {
                            // First block: scale C
                            if (alpha == 0.0) sum = 0.0;
                            else if (alpha == 1.0) sum = C->data[i*C->cols + j];
                            else sum = alpha * C->data[i*C->cols + j];
                        } else {
                            sum = C->data[i*C->cols + j];
                        }
                        for (size_t k = kk; k < k_max; k++)
                            sum += A->data[i*A->cols + k] * B->data[k*B->cols + j];
                        C->data[i*C->cols + j] = sum;
                    }
                }
            }
        }
    }
    return MB_SUCCESS;
}

#ifdef __cplusplus
    }
#endif

#endif  // MICRO_BLAS_H
