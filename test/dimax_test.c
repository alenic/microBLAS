#include "gtest/gtest.h"
#include "microBLAS.h"

TEST(dimax, test_base) {
	double dx1[]={-1.0},  dexp1 = -1.0,
		   dx2[]={1.0,-3.0},  dexp2=1.0,
		   dx3[]={1.6,2.0,-3.0},  dexp3=2.0,
		   dx4[]={1.0,-2.0,1.1,0.0}, dexp4=1.1,
		   dxn[]={1.0,-2.0,3.0,-4.0,-5.0,-6.0,7.0,-8.0,-19.0,-10.0,11.0,-12.0,3.0,-14.0,1.0,6.0}, dexpn=11.0;
    
    unsigned int im;
    double maxval;

    im = dimax(1, dx1, &maxval);
    ASSERT_EQ(maxval, dexp1);
    ASSERT_EQ(im, 0);

    im = dimax(2, dx2, &maxval);
    ASSERT_EQ(maxval, dexp2);
    ASSERT_EQ(im, 0);

    im = dimax(3, dx3, &maxval);
    ASSERT_EQ(maxval, dexp3);
    ASSERT_EQ(im, 1);

    im = dimax(4, dx4, &maxval);
    ASSERT_EQ(maxval, dexp4);
    ASSERT_EQ(im, 2);

    im = dimax(16, dxn, &maxval);
    ASSERT_EQ(maxval, dexpn);
    ASSERT_EQ(im, 10);
}