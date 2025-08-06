#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BLOCK_SIZE 64
#include "microBLAS.h"

int main(void) {
    printf("=== microBLAS Benchmarks Suite ===\n\n");
    srand(0);

    unsigned int sizes[] = { 3, 5, 10, 100, 1000, 2000 };
    const size_t n_sizes = sizeof(sizes) / sizeof(sizes[0]);

    /* --- GEMM benchmarks --- */
    printf("-- GEMM (Matrix×Matrix) --\n");
    for (size_t i = 0; i < n_sizes; ++i) {
        size_t N = sizes[i];

        Matrix A, B, C;
        mcreate_empty(&A, N, N);
        mcreate_empty(&B, N, N);
        mcreate_empty(&C, N, N);

        /* fill A and B with random values in [0,1) */
        for (size_t j = 0; j < N*N; ++j) {
            A.data[j] = (RealType)rand() / (RealType)RAND_MAX;
            B.data[j] = (RealType)rand() / (RealType)RAND_MAX;
        }

        clock_t t0 = clock();
        gemm(&C, &A, &B, (RealType)0.0);
        clock_t t1 = clock();

        double secs = (double)(t1 - t0) / CLOCKS_PER_SEC;
        printf("GEMM  N=%4zu×%-4zu : %8.4f sec\n", N, N, secs);

        mfree(&A);
        mfree(&B);
        mfree(&C);
    }

    /* --- GEMV benchmarks --- */
    printf("\n-- GEMV (Matrix×Vector) --\n");
    for (size_t i = 0; i < n_sizes; ++i) {
        size_t N = sizes[i];

        Matrix M;
        Vector x, y;
        mcreate_empty(&M, N, N);
        vcreate_zero(&x, N);
        vcreate_zero(&y, N);

        /* fill M and x with random values in [0,1) */
        for (size_t j = 0; j < N*N; ++j) {
            M.data[j] = (RealType)rand() / (RealType)RAND_MAX;
        }
        for (size_t j = 0; j < N; ++j) {
            x.data[j] = (RealType)rand() / (RealType)RAND_MAX;
        }

        clock_t t0 = clock();
        gemv(&y, &M, &x, (RealType)0.0);
        clock_t t1 = clock();

        double secs = (double)(t1 - t0) / CLOCKS_PER_SEC;
        printf("GEMV  N=%4zu×%-4zu : %8.4f sec\n", N, N, secs);

        mfree(&M);
        vfree(&x);
        vfree(&y);
    }

    return 0;
}
