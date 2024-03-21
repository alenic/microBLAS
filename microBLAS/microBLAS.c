#include "microBLAS.h"

// ============================ Vectors ================================

// allocate and return the pointer of the an empty vector (not initialized)
RealType *vcreate_empty(unsigned int n) {
    return (RealType *)malloc(n*sizeof(RealType));
}

// allocate and return the pointer of the vector (0,0,...0)
RealType *vcreate_zero(unsigned int n) {
    return (RealType *)calloc(n, sizeof(RealType));
}

// allocate and return the pointer of the the vector (a,a,...a)
RealType *vcreate_const(unsigned int n, const RealType a) {
    RealType *vector = vcreate_empty(n);
    do {
        --n;
        vector[n] = a;
    } while(n);
    return vector;
}

// allocate and return the pointer of the the vector (min_range, min_range+1,...,max_range-1)
RealType *vcreate_range(const RealType min_range, const RealType max_range) {
    if(min_range >= max_range) return 0;

    unsigned int n = max_range - min_range;
    RealType value = min_range;
    RealType *vector = vcreate_empty(n);
    do {
        --n;
        vector[n] = value;
        value++;
    } while(n);
    return vector;
}

// y = (a,a,...,a)
void vset_const(unsigned int n, const RealType a, RealType *y) {
    do {
        --n;
        y[n] = a;
    } while(n);
}

// y = x
void vcopy(unsigned int n, const RealType *x, RealType *y) {
    do {
        --n;
        y[n] = x[n];
    } while(n);
}


// y = a*y
void vscale(unsigned int n, const RealType a, RealType *y)
{
    if(a == 0.0) {
        vset_const(n, 0.0, y);
    } else if(a != 1.0) {
        do {
            --n;
            y[n] = a*y[n];
        } while(n);
    }
}

// y = x1 + x2
void vxpx(unsigned int n, const RealType *x1, const RealType *x2, RealType *y)
{
    do {
        --n;
        y[n] += x1[n] + x2[n];
    } while(n);
}

// y = a*x + y
void vaxpy(unsigned int n, const RealType a, const RealType *x, RealType *y)
{
    if(a == 0.0) {
        return;
    }
    if(a == 1.0) {
        do {
            --n;
            y[n] += x[n];
        } while(n);
    } else {
        do {
            --n;
            y[n] += a*x[n];
        } while(n);
    }
}

// return the dot product <a, b>
RealType dot(unsigned int n, const RealType *a, const RealType *b) {
    RealType sum = 0.0;

    do {
        --n;
        sum += a[n]*b[n];
    } while(n);

    return sum;
}

// return the sum of the components of the vector x
RealType vsum(unsigned int n, const RealType *x) {
    RealType sum = 0.0;
    do {
        --n;
        sum += x[n];
    } while(n);

    return sum;
}

// return the L2-squared norm of a vector x
RealType l2_sq(unsigned int n, const RealType *x) {
    RealType sum = 0.0;

    do {
        --n;
        sum += x[n]*x[n];
    } while(n);

    return sum;
}

// return the L2 norm of a vector x
RealType l2(unsigned int n, const RealType *x) {
    return (RealType)sqrt(l2_sq(n, x));
}

// return the L2-squared norm of the vector x1-x2
RealType l2_dist_sq(unsigned int n, const RealType *x1, const RealType *x2) {
    RealType sum = 0.0;
    RealType delta;
    do {
        --n;
        delta = x1[n] - x2[n];
        sum += delta*delta;
    } while(n);

    return sum;
}

// return the L2 norm of the vector x1-x2
RealType l2_dist(unsigned int n, const RealType *x1, const RealType *x2) {
    return (RealType)sqrt(l2_dist_sq(n, x1, x2));
}

// return the L1 norm of a vector x
RealType l1(unsigned int n, const double *x) {
    RealType sum = 0.0;
    do {
        --n;
        if(x[n] < 0)
            sum -= x[n];
        else
            sum += x[n];
    } while(n);

    return sum;
}

// return the minimum value of the vector x
RealType vmin(unsigned int n, const RealType *x) {
    RealType min_val;
    --n;
    min_val = x[n];
    while(n) {
        --n;
        if(x[n] < min_val) {
            min_val = x[n];
        }
    }

    return min_val;
}

// return the maximum value of the vector x
RealType vmax(unsigned int n, const RealType *x) {
    RealType max_val;
    --n;
    max_val = x[n];
    while(n) {
        --n;
        if(x[n] > max_val) {
            max_val = x[n];
        }
    }

    return max_val;
}

// return the index of the minimum value of the vector x
unsigned int vimin(unsigned int n, const RealType *x) {
    unsigned int min_index;
    RealType min_val;
    min_index = n;

    --n;
    min_val = x[n];
    while(n) {
        --n;
        if(x[n] < min_val) {
            min_val = x[n];
            min_index = n;
        }
    }

    return min_index;
}

// return the index of the maximum value of the vector x
unsigned int vimax(unsigned int n, const RealType *x) {
    unsigned int max_index;
    RealType max_val;
    max_index = n;

    --n;
    max_val = x[n];
    while(n) {
        --n;
        if(x[n] > max_val) {
            max_val = x[n];
            max_index = n;
        }
    }

    return max_index;
}

// ============================ Matrix ================================

// allocate and return the pointer of the an empty vector (not initialized)
RealType *mcreate_empty(unsigned int rows, unsigned int cols) {
    return (RealType *)malloc(rows*cols*sizeof(RealType));
}

// allocate and return the pointer of the vector (0,0,...,0)
RealType *mcreate_zero(unsigned int rows, unsigned int cols) {
    return (RealType *)calloc(rows*cols, sizeof(RealType));
}

// allocate and return the pointer of the the vector (a,a,...,a)
RealType *mcreate_const(unsigned int rows, unsigned int cols, const RealType a) {
    RealType *matrix = mcreate_empty(rows, cols);
    unsigned int n = rows*cols;
    do {
        --n;
        matrix[n] = a;
    } while(n);

    return matrix;
}

// general cumulative matrix-vector multiplication: y = A*x + b*y (WARNING it doesn't check len(x) == cols)
void gemv(unsigned int rows, unsigned int cols, const RealType *A, const RealType *x, RealType b, RealType *y)
{
    unsigned int i, j, ilda=0;
    for(i=0; i<rows; i++) {
        if(b == 0.0) y[i] = 0;
        else if(b != 1.0) y[i] = b*y[i];
        for(j=0; j<cols; j++) {
            y[i] += A[ilda+j]*x[j];
        }
        ilda += cols;
    }
}


// general matrix-matrix multiplication: Y = X1*X2
// Y is a (rows_x1, cols_x2) matrix
// X1 is a (rows_x1, cols_x1) matrix
// X2 is a (cols_x1, cols_x2)   [cols_x1 == rows_x2]
void gemm(unsigned int rows_x1,
          unsigned int cols_x1,
          unsigned int cols_x2,
          const RealType *X1,
          const RealType *X2,
          RealType *Y
) {
    unsigned int i, j, ilda_y=0, ilda_x1=0, ilda_x2=0;

    for (int i=0; i<rows_x1; i++) {
        for (int j = 0; j<cols_x2; j++) {
            Y[ilda_y+j] = 0;
            ilda_x2 = 0;
            for (int k = 0; k<cols_x1; k++) {
                Y[ilda_y+j] += X1[ilda_x1+k] * X2[ilda_x2+j];
                ilda_x2 += cols_x2;
            }
        }
        ilda_y += cols_x2;
        ilda_x1 += cols_x1;
    }
}
