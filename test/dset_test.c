#include "gtest/gtest.h"
#include "microBLAS.h"


TEST(dset, test_base) {
	double dact1[1], dexp1[]={1.0},
		   dact2[2], dexp2[]={1.0,1.0},
		   dact3[3], dexp3[]={1.0,1.0,1.0},
		   dact4[4], dexp4[]={1.0,1.0,1.0,1.0},
		   dactn[16], dexpn[]={1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
	double da=1.0;

	dset(1, &da, dact1);
	dset(2, &da, dact2);
	dset(3, &da, dact3);
	dset(4, &da, dact4);
	dset(16, &da, dactn);
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