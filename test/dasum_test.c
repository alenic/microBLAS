#include "gtest/gtest.h"
#include "microBLAS.h"

TEST(dasum, test_base) {
	double dx1[]={-1.0},
		   dx2[]={1.0,-2.0},
		   dx3[]={-1.0,2.0,-3.0},
		   dx4[]={1.0,-2.0,3.0,-4.0},
		   dxn[]={1.0,-2.0,3.0,-4.0,-5.0,-6.0,7.0,-8.0,9.0,-10.0,11.0,-12.0,13.0,-14.0,15.0,16.0};
	unsigned int N;
    double eps = 1e-16;
    
	N=1;
    ASSERT_NEAR(dasum(N,dx1), (N*(N+1))/2,eps);
    N=2;
    ASSERT_NEAR(dasum(N,dx2), (N*(N+1))/2,eps);
    N=3;
    ASSERT_NEAR(dasum(N,dx3), (N*(N+1))/2,eps);
    N=4;
    ASSERT_NEAR(dasum(N,dx4), (N*(N+1))/2,eps);
    N=16;
    ASSERT_NEAR(dasum(N,dxn), (N*(N+1))/2,eps);
}