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

// Y = A + diag(d1,d2,...,dn)
static inline void madddiag(unsigned int n, const RealType *A, const RealType *diag, RealType *Y) {
    unsigned int n1 = n+1;
    for (unsigned int i = 0; i < n; i++) {
        Y[i*n1] += A[i*n1] + diag[i];
    }
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