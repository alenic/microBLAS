#include "gtest/gtest.h"
#include "microBLAS.h"

TEST(dmax, test_base) {
	double dx1[]={-1.0},  dexp1 = -1.0,
		   dx2[]={1.6,-3.0},  dexp2=1.6,
		   dx3[]={1.6,2.0,-3.0},  dexp3=2.0,
		   dx4[]={11.0,-2.0,1.0,0.0}, dexp4=11.0,
		   dxn[]={1.0,-2.0,3.0,-4.0,-5.0,-6.0,7.0,-8.0,-19.0,-10.0,11.0,-12.0,13.0,-14.0,1.0,-16.0}, dexpn=13.0;
    
    ASSERT_EQ(dmax(1,dx1), dexp1);
    ASSERT_EQ(dmax(2,dx2), dexp2);
    ASSERT_EQ(dmax(3,dx3), dexp3);
    ASSERT_EQ(dmax(4,dx4), dexp4);
    ASSERT_EQ(dmax(16,dxn), dexpn);
}