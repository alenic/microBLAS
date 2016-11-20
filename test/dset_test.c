#include "gtest/gtest.h"
#include "microBLAS.h"


TEST(dset, test_base) {
	double dact1[1], dexp1[]={1.0},
		   dact2[2], dexp2[]={2.0,2.0},
		   dact3[3], dexp3[]={3.0,3.0,3.0},
		   dact4[4], dexp4[]={4.0,4.0,4.0,4.0},
		   dactn[16], dexpn[]={5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0};
	double da=1.0;

	dset(1, 1.0, dact1);
	dset(2, 2.0, dact2);
	dset(3, 3.0, dact3);
	dset(4, 4.0, dact4);
	dset(16, 5.0, dactn);
    for (int i=0; i<1; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dact1[i],dexp1[i]);
	}
    for (int i=0; i<2; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dact2[i],dexp2[i]);
	}
    for (int i=0; i<3; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dact3[i],dexp3[i]);
	}
    for (int i=0; i<4; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dact4[i],dexp4[i]);
	}
    for (int i=0; i<16; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dactn[i],dexpn[i]);
	}
}