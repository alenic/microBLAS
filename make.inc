# Compiler
CC=gcc
CPP=g++
CFLAGS=-O3
CPPFLAGS=-O3 -D__cpp

# Static lib
LIB_VERSION=1.0.0
LIB_OBJECTS=darray.o dzeros.o dset.o dcopy.o dsum.o dasum.o ddot.o dswap.o dnorm.o dnorm2.o dmin.o dimin.o dmax.o dimax.o dscal.o dvcal.o daxpy.o
LIB_A_TARGET=libmicroBLAS.a

# Dynamic lib
LIB_SO_TARGET=libmicroBLAS.so.$(LIB_VERSION)

# Test
EXECUTABLE=mainTest.out
# Google test header file
GTEST_H=../googletest/googletest/include
# Google test library
GTEST_LIB=../googletest/googlemock/gtest/libgtest.a
