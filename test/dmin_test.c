#include "gtest/gtest.h"
#include "microBLAS.h"

TEST(dmin, test_base) {
	double dx1[]={-1.0},  dexp1 = -1.0,
		   dx2[]={1.0,-3.0},  dexp2=-3.0,
		   dx3[]={1.6,2.0,3.0},  dexp3=1.6,
		   dx4[]={11.0,-2.0,1.0,0.0}, dexp4=-2.0,
		   dxn[]={1.0,-2.0,3.0,-4.0,-5.0,-6.0,7.0,-8.0,-19.0,-10.0,11.0,-12.0,13.0,-14.0,15.0,16.0}, dexpn=-19.0;
    
    ASSERT_EQ(dmin(1,dx1), dexp1);
    ASSERT_EQ(dmin(2,dx2), dexp2);
    ASSERT_EQ(dmin(3,dx3), dexp3);
    ASSERT_EQ(dmin(4,dx4), dexp4);
    ASSERT_EQ(dmin(16,dxn), dexpn);
}