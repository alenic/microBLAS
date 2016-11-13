#include "gtest/gtest.h"
#include "microBLAS.h"


TEST(dzeros, test_base) {
	double *dact1, dexp1[]={0.0},
		   *dact2, dexp2[]={0.0,0.0},
		   *dact3, dexp3[]={0.0,0.0,0.0},
		   *dact4, dexp4[]={0.0,0.0,0.0,0.0},
		   *dactn, dexpn[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

	dact1 = dzeros(1);
	dact2 = dzeros(2);
	dact3 = dzeros(3);
	dact4 = dzeros(4);
	dactn = dzeros(16);

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

	free(dact1);
	free(dact2);
	free(dact3);
	free(dact4);
	free(dactn);
}