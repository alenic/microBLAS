#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "microBLAS.h"

// Simple assert macro for testing
#define ASSERT(cond, msg) \
    do { if (!(cond)) { \
        printf("[FAIL] %s\n", msg); \
        exit(EXIT_FAILURE); \
    } else { \
        printf("[PASS] %s\n", msg); \
    }} while (0)

int main(void) {
    printf("=== microBLAS Test Suite ===\n");

    // ----------------- Vector creation -----------------
    RealType *v1 = vcreate_empty(5);
    ASSERT(v1 != NULL, "vcreate_empty allocates memory");
    vfree(v1);

    RealType *v2 = vcreate_zero(3);
    ASSERT(v2[0] == 0 && v2[1] == 0 && v2[2] == 0, "vcreate_zero initializes to 0");
    vfree(v2);

    RealType *v3 = vcreate_const(4, 2.0);
    ASSERT(v3[0] == 2.0 && v3[3] == 2.0, "vcreate_const initializes with constant");
    vfree(v3);

    RealType *v4 = vcreate_range(1, 4);
    ASSERT(v4[0] == 1 && v4[1] == 2 && v4[2] == 3, "vcreate_range generates sequence");
    vfree(v4);

    // ----------------- Basic vector ops -----------------
    RealType arr[3] = {1, 2, 3};
    RealType out[3];
    vset_const(3, 5.0, out);
    ASSERT(out[0] == 5 && out[2] == 5, "vset_const sets all elements");

    vcopy(3, arr, out);
    ASSERT(out[0] == 1 && out[2] == 3, "vcopy copies correctly");

    vscale(3, 2.0, out);
    ASSERT(out[0] == 2 && out[2] == 6, "vscale multiplies elements");

    RealType x1[3] = {1, 1, 1};
    RealType x2[3] = {2, 2, 2};
    RealType y[3] = {0, 0, 0};
    vxpx(3, x1, x2, y);
    ASSERT(y[0] == 3 && y[2] == 3, "vxpx adds two vectors");

    RealType y2[3] = {1, 1, 1};
    vaxpy(3, 2.0, x1, y2); // y = 2*x + y
    ASSERT(y2[0] == 3 && y2[2] == 3, "vaxpy computes a*x + y");

    // ----------------- Norms and reductions -----------------
    RealType d = dot(3, arr, arr);
    ASSERT(fabs(d - 14.0) < 1e-6, "dot computes dot product");

    RealType s = vsum(3, arr);
    ASSERT(fabs(s - 6.0) < 1e-6, "vsum computes sum");

    RealType l2s = l2_sq(3, arr);
    ASSERT(fabs(l2s - 14.0) < 1e-6, "l2_sq computes squared L2 norm");

    RealType l2n = l2(3, arr);
    ASSERT(fabs(l2n - sqrt(14.0)) < 1e-6, "l2 computes L2 norm");

    RealType arr2[3] = {2, 3, 4};
    RealType l2ds = l2_dist_sq(3, arr, arr2);
    ASSERT(fabs(l2ds - 3.0) < 1e-6, "l2_dist_sq works");

    RealType l2d = l2_dist(3, arr, arr2);
    ASSERT(fabs(l2d - sqrt(3.0)) < 1e-6, "l2_dist works");

    RealType arr3[3] = {-1, 2, -3};
    RealType l1n = l1(3, arr3);
    ASSERT(fabs(l1n - 6.0) < 1e-6, "l1 computes L1 norm");

    RealType arr4[4] = {7, 2, 9, 1};
    ASSERT(vmin(4, arr4) == 1, "vmin finds minimum");
    ASSERT(vmax(4, arr4) == 9, "vmax finds maximum");
    ASSERT(vimin(4, arr4) == 3, "vimin finds min index");
    ASSERT(vimax(4, arr4) == 2, "vimax finds max index");

    // ----------------- Matrix creation -----------------
    RealType *M1 = mcreate_empty(2, 3);
    ASSERT(M1 != NULL, "mcreate_empty allocates");
    mfree(M1);

    RealType *M2 = mcreate_zero(2, 2);
    ASSERT(M2[0] == 0 && M2[3] == 0, "mcreate_zero initializes to 0");
    mfree(M2);

    RealType *M3 = mcreate_const(2, 2, 4.0);
    ASSERT(M3[0] == 4 && M3[3] == 4, "mcreate_const initializes to constant");
    mfree(M3);

    // ----------------- gemv -----------------
    RealType A[6] = {1, 2, 3, 4, 5, 6}; // 2x3 matrix row-major
    RealType xv[3] = {1, 1, 1};
    RealType yv[2] = {0, 0};
    gemv(2, 3, A, xv, 0.0, yv); // y = A*x
    ASSERT(fabs(yv[0] - 6.0) < 1e-6 && fabs(yv[1] - 15.0) < 1e-6, "gemv works");

    // ----------------- gemm -----------------
    RealType X1[6] = {1, 2, 3, 4, 5, 6}; // 2x3
    RealType X2[6] = {7, 8, 9, 10, 11, 12}; // 3x2
    RealType Y[4] = {0, 0, 0, 0}; // 2x2
    gemm(2, 3, 2, X1, X2, Y, 0.0); // Y = X1*X2
    ASSERT(fabs(Y[0] - 58.0) < 1e-6 && fabs(Y[1] - 64.0) < 1e-6 &&
           fabs(Y[2] - 139.0) < 1e-6 && fabs(Y[3] - 154.0) < 1e-6,
           "gemm works");

    printf("\nAll tests passed successfully!\n");
    return 0;
}
