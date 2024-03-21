#include "gtest/gtest.h"
#include "microBLAS.h"


TEST(test_gemv, test_base) {

    RealType A1[] = {12.0},
             dx1[] = {3.0},
             A2[] = {12.0,10.0, 9.0 ,1.0},
             dx2[] = {-1.0, 9.0},
             A3[] = {2.0, 1.0, 3.0, 6.0, 7.0, 2.5, -1.0,-2.0, 8.0},
             dx3[] = {-1.0, 9.0, 4.0},
             A4[] = {2.0, 1.0, 3.0, 9.0, 6.0, 7.0, 2.5,-1.0, -1.0,-2.0, 8.0, 3.0, 2.0, 1.0, 0.0, 5.0},
             dx4[] = {1.0, -9.0, 4.0, 2.0},
             out1[1],
             out2[2],
             out3[3],
             out4[4];

    RealType dexp1[] = {36.0},
           dexp2[] = {78.0, 0.0},
           dexp3[] = {19.0, 67.0, 15.0},
           dexp4[] = {23.0,-49.0,55.0,3.0};

    double eps = 1e-16;
    
    // generic tests
    gemv(1,1,A1,dx1,0.0,out1);
    gemv(2,2,A2,dx2,0.0,out2);
    gemv(3,3,A3,dx3,0.0,out3);
    gemv(4,4,A4,dx4,0.0,out4);

    for (int i=0; i<1; i++) {
        SCOPED_TRACE(i);
        ASSERT_NEAR(out1[i],dexp1[i],eps);
    }
    for (int i=0; i<2; i++) {
        SCOPED_TRACE(i);
        ASSERT_NEAR(out2[i],dexp2[i],eps);
    }
    for (int i=0; i<3; i++) {
        SCOPED_TRACE(i);
        ASSERT_NEAR(out3[i],dexp3[i],eps);
    }
    for (int i=0; i<4; i++) {
        SCOPED_TRACE(i);
        ASSERT_NEAR(out4[i],dexp4[i],eps);
    }
}