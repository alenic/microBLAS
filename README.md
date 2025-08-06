# microBLAS
```
            _                  ____  _        _    ____  
  _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___|
 | '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \
 | | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
 |_| |_| |_|_|\___|_|  \___/  |____/|_____/__ /   \_\____/
```

A simple, header-only implementation of BLAS (Basic Linear Algebra Subprograms), optimized for both **desktop** and **embedded** systems using a minimal C API.
Designed for ease of integration into small numerical projects or microcontroller code bases.

* **Header-only** (just `#include "microBLAS.h"`)
* No external dependencies beyond the C standard library (`<stdlib.h>`, `<math.h>`)
* Supports both `float` (default) and `double` precision via `REAL_TYPE_DOUBLE`
* Implements essential BLAS routines:

  * **Level 1 (Vector):** allocation, deallocation, copy, scale, add, A·X+Y (`axpy`), dot product, norms (L1, L2, L∞), min/max, index-of-min/max
  * **Level 2 (Matrix–Vector):** `gemv`
  * **Level 3 (Matrix–Matrix):** blocked `gemm` with accumulation

**Row-major** storage for matrices.

---

## Quickstart

1. **Include the header** in your C source:

   ```c
   #include "microBLAS.h"
   ```

2. **Choose precision** (optional). By default, `RealType` is `float`. To use `double`, either:

   ```c
   #define REAL_TYPE_DOUBLE
   #include "microBLAS.h"
   ```

   or pass at compile time:

   ```sh
   gcc -DREAL_TYPE_DOUBLE -o your_program your_program.c -lm
   ```

3. **Compile** your program as usual:

   ```sh
   gcc -o example example.c -lm
   ```

---

## Core Types

```c
// Vector of length n
typedef struct {
    RealType *data;
    size_t     n;
} Vector;

// Matrix with rows×cols elements (row-major)
typedef struct {
    RealType *data;
    size_t    rows;
    size_t    cols;
} Matrix;

// Error codes returned by each function (MBError)
enum { MB_SUCCESS, MB_ERR_ALLOC, MB_ERR_DIM_MISMATCH, MB_ERR_NULL_PTR, MB_ERR_DIV_BY_ZERO, MB_ERR_UNKNOWN };
```

Memory management and validity checks are performed in each routine to help catch errors.

---

## Examples

### Vector Allocation and Operations

```c
#include "microBLAS.h"
#include <stdio.h>

int main(void) {
    // Create vectors a and b of length 3
    Vector a, b, y;
    vcreate_const(&a, 3, (RealType)1.0);   // a = [1, 1, 1]
    vcreate_const(&b, 3, (RealType)2.0);   // b = [2, 2, 2]
    vcreate_zero(&y, 3);                  // y = [0, 0, 0]

    // y = 2*a + y
    vaxpy(&y, (RealType)2.0, &a);

    // dot product a·b
    RealType dp;
    vdot(&dp, &a, &b);
    printf("dot(a,b) = %f\n", dp);

    // L2 norm of a
    RealType norm;
    vl2(&norm, &a);
    printf("||a||₂ = %f\n", norm);

    // Cleanup
    vfree(&a);
    vfree(&b);
    vfree(&y);
    return 0;
}
```

### Matrix–Vector Multiplication (`gemv`)

```c
#include "microBLAS.h"
#include <stdio.h>

int main(void) {
    // Define a 2×3 matrix A and vector x of length 3
    Matrix A;
    Vector x, y;

    mcreate_const(&A, 2, 3, (RealType)1.0); // A = [[1 1 1], [1 1 1]]
    vcreate_const(&x, 3, (RealType)1.0);     // x = [1, 1, 1]
    vcreate_zero(&y, 2);                     // y = [0, 0]

    // Compute y = A*x + 0·y
    gemv(&y, &A, &x, (RealType)0.0);

    printf("y = [%f, %f]\n", y.data[0], y.data[1]);

    mfree(&A);
    vfree(&x);
    vfree(&y);
    return 0;
}
```

### Matrix–Matrix Multiplication (`gemm`)

```c
#include "microBLAS.h"
#include <stdio.h>

int main(void) {
    Matrix A, B, C;

    // A: 2×3, B: 3×2
    mcreate_empty(&A, 2, 3);
    mcreate_empty(&B, 3, 2);
    mcreate_zero(&C, 2, 2);

    // Fill A = [[1,2,3], [4,5,6]]
    for (size_t i = 0; i < 6; ++i) A.data[i] = (RealType)(i + 1);
    // Fill B = [[7,8], [9,10], [11,12]]
    for (size_t i = 0; i < 6; ++i) B.data[i] = (RealType)(7 + i);

    // Compute C = A*B
    gemm(&C, &A, &B, (RealType)0.0);

    // Print C
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            printf("%f ", C.data[i * 2 + j]);
        }
        printf("\n");
    }

    mfree(&A);
    mfree(&B);
    mfree(&C);
    return 0;
}
```

---

## Testing

A `Makefile` is provided:

```makefile
# Build tests
gcc -o test tests.c -lm

# Run
test: test
	./test

clean:
	rm -f test
```

Execute:

```sh
make
make test
```

---

## Notes

**microBLAS** is designed for **lightweight** and **portable** use cases. It is **not** a substitute for high-performance BLAS implementations (e.g., OpenBLAS, Intel MKL) on large-scale problems. Instead, it offers simplicity and ease of integration for embedded systems and small-scale numerical tasks.
