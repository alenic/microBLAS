#include "gtest/gtest.h"
#include "microBLAS.h"

TEST(dasum, test_base) {
	double dact1[]={-1.0},
		   dact2[]={1.0,-2.0},
		   dact3[]={-1.0,2.0,-3.0},
		   dact4[]={1.0,-2.0,3.0,-4.0},
		   dactn[]={1.0,-2.0,3.0,-4.0,-5.0,-6.0,7.0,-8.0,9.0,-10.0,11.0,-12.0,13.0,-14.0,15.0,16.0};
	unsigned int N;
    double eps = 1e-16;
    
	N=1;
    ASSERT_NEAR(dasum(N,dact1), (N*(N+1))/2,eps);
    N=2;
    ASSERT_NEAR(dasum(N,dact2), (N*(N+1))/2,eps);
    N=3;
    ASSERT_NEAR(dasum(N,dact3), (N*(N+1))/2,eps);
    N=4;
    ASSERT_NEAR(dasum(N,dact4), (N*(N+1))/2,eps);
    N=16;
    ASSERT_NEAR(dasum(N,dactn), (N*(N+1))/2,eps);
}