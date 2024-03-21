#include "gtest/gtest.h"
#include "microBLAS.h"

TEST(test_vsum, test_base) {
    RealType dx1[]={-1.0}, dexp1=-1.0,
           dx2[]={1.0,-2.0}, dexp2=-1.0,
           dx3[]={-1.0,2.0,-3.0}, dexp3=-2.0,
           dx4[]={1.0,-2.0,3.0,-4.0}, dexp4=-2.0,
           dxn[]={1.0,-2.0,3.0,-4.0,-5.0,-6.0,7.0,-8.0,9.0,-10.0,11.0,-12.0,13.0,-14.0,15.0,16.0}, dexpn=14.0;
    unsigned int N;
    double eps = 1e-16;
    
    N=1;
    ASSERT_NEAR(vsum(N,dx1), dexp1, eps);
    N=2;
    ASSERT_NEAR(vsum(N,dx2), dexp2, eps);
    N=3;
    ASSERT_NEAR(vsum(N,dx3), dexp3, eps);
    N=4;
    ASSERT_NEAR(vsum(N,dx4), dexp4, eps);
    N=16;
    ASSERT_NEAR(vsum(N,dxn), dexpn, eps);

}

