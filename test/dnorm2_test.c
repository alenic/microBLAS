#include "gtest/gtest.h"
#include "microBLAS.h"

TEST(dnorm2, test_base) {
	double dx1[]={-1.0},  dexp1 = 1.0,
		   dx2[]={1.0,-3.0},  dexp2=10.0,
		   dx3[]={-1.0,-2.0,-3.0},  dexp3=14.0,
		   dx4[]={11.0,-2.0,1.0,-3.0}, dexp4=135.0;

    double eps = 1e-16;
    
    ASSERT_NEAR(dnorm2(1,dx1), dexp1, eps);
    ASSERT_NEAR(dnorm2(2,dx2), dexp2, eps);
    ASSERT_NEAR(dnorm2(3,dx3), dexp3, eps);
    ASSERT_NEAR(dnorm2(4,dx4), dexp4, eps);
}