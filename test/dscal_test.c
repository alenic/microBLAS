#include "gtest/gtest.h"
#include "microBLAS.h"


TEST(dscal, test_base) {
	double dact1[]={1.0},da1=2.5,
		   dexp1[]={2.5},
		   dact2[]={4.0,2.0},da2=1.0/2.0,
		   dexp2[]={2.0,1.0},
		   dact3[]={1.0,2.0,3.0},da3=0.1,
		   dexp3[]={0.1,0.2,0.3},
		   dact4[]={4.0,3.0,2.0,1.0},da4=10.0,
		   dexp4[]={40.0,30.0,20.0,10.0},
		   dactn[]={1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0}, dan=2.0,
		   dexpn[]={2.0,4.0,6.0,8.0,10.0,12.0,14.0,16.0,18.0,20.0,22.0,24.0,26.0,28.0,30.0,32.0};
	double dzero1[]={0.0},
		   dzero2[]={0.0,0.0},
		   dzero3[]={0.0,0.0,0.0},
		   dzero4[]={0.0,0.0,0.0,0.0},
		   dzeron[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	double eps = 1e-16;
	// generic da tests
	dscal(1, da1, dact1);
	dscal(2, da2, dact2);
	dscal(3, da3, dact3);
	dscal(4, da4, dact4);
	dscal(16, dan, dactn);
    for (int i=0; i<1; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dact1[i],dexp1[i],eps);
	}
    for (int i=0; i<2; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dact2[i],dexp2[i],eps);
	}
    for (int i=0; i<3; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dact3[i],dexp3[i],eps);
	}
    for (int i=0; i<4; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dact4[i],dexp4[i],eps);
	}
    for (int i=0; i<16; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dactn[i],dexpn[i],eps);
	}

	// da=1 tests
	dscal(1, 1.0, dact1);
	dscal(2, 1.0, dact2);
	dscal(3, 1.0, dact3);
	dscal(4, 1.0, dact4);
	dscal(16, 1.0, dactn);

    for (int i=0; i<1; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dact1[i],dexp1[i],eps);
	}
    for (int i=0; i<2; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dact2[i],dexp2[i],eps);
	}
    for (int i=0; i<3; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dact3[i],dexp3[i],eps);
	}
    for (int i=0; i<4; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dact4[i],dexp4[i],eps);
	}
    for (int i=0; i<16; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_NEAR(dactn[i],dexpn[i],eps);
	}

	// da=0 tests
	dscal(1, 0.0, dact1);
	dscal(2, 0.0, dact2);
	dscal(3, 0.0, dact3);
	dscal(4, 0.0, dact4);
	dscal(16, 0.0, dactn);

    for (int i=0; i<1; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dact1[i],dzero1[i]);
	}
    for (int i=0; i<2; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dact2[i],dzero2[i]);
	}
    for (int i=0; i<3; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dact3[i],dzero3[i]);
	}
    for (int i=0; i<4; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dact4[i],dzero4[i]);
	}
    for (int i=0; i<16; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dactn[i],dzeron[i]);
	}
}