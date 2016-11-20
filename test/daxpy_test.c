#include "gtest/gtest.h"
#include "microBLAS.h"


TEST(daxpy, test_base) {
	double da1=2.5,
		   x1[]={1.0},
		   y1[]={2.0},
		   dexp1[]={4.5},
		   dexp_one1[]={5.5},
		   da2=2.0,
		   x2[]={0.5,2.0},
		   y2[]={1.5,3.5},
		   dexp2[]={2.5,7.5},
		   dexp_one2[]={3.0,9.5},
		   da3=2.0,
		   x3[]={0.5,2.0,1.5},
		   y3[]={1.5,3.5,0.0},
		   dexp3[]={2.5,7.5,3.0},
		   dexp_one3[]={3.0,9.5,4.5},
		   da4=2.0,
		   x4[]={0.5,2.0,1.5,9.0},
		   y4[]={1.5,3.5,0.0,1.2},
		   dexp4[]={2.5,7.5,3.0,19.2},
		   dexp_one4[]={3.0,9.5,4.5,28.2};

	double eps = 1e-16;
	// generic da tests
	daxpy(1, da1, x1, y1);
	daxpy(2, da2, x2, y2);
	daxpy(3, da3, x3, y3);
	daxpy(4, da4, x4, y4);

    for (int i=0; i<1; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(y1[i],dexp1[i],eps);
	}
    for (int i=0; i<2; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(y2[i],dexp2[i],eps);
	}
    for (int i=0; i<3; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(y3[i],dexp3[i],eps);
	}
    for (int i=0; i<4; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(y4[i],dexp4[i],eps);
	}


	// da=1 tests
	daxpy(1, 1.0, x1, y1);
	daxpy(2, 1.0, x2, y2);
	daxpy(3, 1.0, x3, y3);
	daxpy(4, 1.0, x4, y4);

    for (int i=0; i<1; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(y1[i],dexp_one1[i],eps);
	}
    for (int i=0; i<2; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(y2[i],dexp_one2[i],eps);
	}
    for (int i=0; i<3; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(y3[i],dexp_one3[i],eps);
	}
    for (int i=0; i<4; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(y4[i],dexp_one4[i],eps);
	}
}