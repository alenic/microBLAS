# microBLAS

A simple, tiny and efficient BLAS (Basic Linear Algebra Subprograms) library, designed for PC and Microcontrollers.

TODO:
- Level 3 Dgemm routine (y = da*A*B + db*y)
- For every subroutines a fixed size vector/matrix routine for n=2,3,4, for example:

  dgemv(m, n, lda, da, A, dx, db, dy)   => dgemv2(lda, da, A[4], dx[2], db, dy[2])
                                           dgemv3(lda, da, A[9], dx[3], db, dy[3])
                                           ...


## microBLAS's directory structure

In the root folder:
  * **include**: Inlcude files
  * **src**: Source files
  * **test**: Unit tests and integration tests (Using Google test framework)
  * **obj**: Object files
  * **lib**: Dynamic (.so) and static libraries (.a)

  

 ## Install


1. Install Google Test framework before. Follow instructions in [Google Test](https://github.com/google/googletest)

2. Modify the Google Test section in `make.inc` with the right folders where is installed google test
```
# Google test header file
GTEST_H=../googletest/googletest/include
# Google test library
GTEST_LIB=../googletest/googlemock/gtest/libgtest.a
```
 3. In terminal

```
$ make all
```


