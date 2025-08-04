```
            _                  ____  _        _    ____  
  _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
 | '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
 | | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
 |_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 
```

A simple, tiny, and efficient BLAS (Basic Linear Algebra Subprograms) library.  
Designed for both **PC** and **microcontrollers**, implemented as a **single header file**.

- Header-only: just `#include "microBLAS.h"`
- No external dependencies (`libm` only if using `<math.h>`)
- Supports both `float` and `double` precision via a macro
- Implements essential BLAS routines:
  - **Level 1 (Vector):** dot product, norms (L1, L2, L∞), scaling, addition
  - **Level 2 (Matrix–Vector):** `gemv`
  - **Level 3 (Matrix–Matrix):** `gemm` with optional accumulation `+ b*Y`
- Works on desktop and embedded systems
- Lightweight alternative to heavy BLAS libraries

**The matrix format is row major order**

## Usage

Include microBLAS.h in your c file


```c
#include "microBLAS.h"

int main() {
    RealType v[3] = {1, 2, 3};
    RealType norm = l2(3, v);
}
```

By default, RealType is float.

To switch to double, define the macro before including:

```c
#define REAL_TYPE_DOUBLE
#include "microBLAS.h"

int main() {
    RealType x = 3.14159;
    // x is a double now
}
```

or pass it at compile time:


```
gcc -DREAL_TYPE_DOUBLE -o your_program your_program.c -lm
```

## Examples

### Vector Operations
```c
RealType a[3] = {1, 2, 3};
RealType b[3] = {4, 5, 6};
RealType y[3] = {0, 0, 0};

vaxpy(3, 2.0, a, y); // y = 2*a + y
RealType dotp = dot(3, a, b); // dot product
RealType norm = l2(3, a);     // L2 norm
```

### Matrix–Vector Multiplication
```c
RealType A[6] = {1, 2, 3, 4, 5, 6}; // 2x3 matrix
RealType x[3] = {1, 1, 1};
RealType y[2] = {0, 0};

gemv(2, 3, A, x, 0.0, y); // y = A*x
```

### Matrix–Matrix Multiplication
```c
RealType X1[6] = {1, 2, 3, 4, 5, 6};     // 2x3
RealType X2[6] = {7, 8, 9, 10, 11, 12};  // 3x2
RealType Y[4]  = {0, 0, 0, 0};           // 2x2

gemm(2, 3, 2, X1, X2, Y, 0.0); // Y = X1*X2
```

## Test

A Makefile is provided to test the library.

```
# Build the test program
make

# Run the tests
make run
```
To clean up

```
# Clean up
make clean
```

## Notes

**microBLAS** is designed to be lightweight and portable, not a replacement for highly optimized libraries like OpenBLAS, BLIS, or Intel MKL.
For small to medium workloads (e.g. embedded systems, simple numerical projects), it provides excellent simplicity with reasonable speed.
For large-scale linear algebra, prefer a full BLAS/LAPACK library.