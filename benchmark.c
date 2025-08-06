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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BLOCK_SIZE 64
#include "microBLAS.h"


int main(void) {
    printf("=== microBLAS Benchmarks Suite ===\n");

    srand(0);
    
    unsigned int sizes[] = {3, 5, 10, 100, 1000};
    unsigned int n_size = 5;

    for(unsigned int k=0; k<n_size; k++) {
        int N = sizes[k];
        RealType *A = mcreate_empty(N, N);
        RealType *B = mcreate_empty(N, N);
        RealType *C = mcreate_empty(N, N);

        for(unsigned int i=0; i<N*N; i++) {
            A[i] = (RealType)rand()/(RealType)(RAND_MAX);
            B[i] = (RealType)rand()/(RealType)(RAND_MAX);
        }

        clock_t tic = clock();
        gemm(N, N, N, A, B, 0.0, C);
        clock_t toc = clock();
        printf("DGEMM N=%dx%d: %f seconds\n", N, N, (double)(toc - tic) / CLOCKS_PER_SEC);

        mfree(C);
        mfree(B);
        mfree(A);
    }



    return 0;
}
