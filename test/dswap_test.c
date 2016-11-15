#include "gtest/gtest.h"
#include "microBLAS.h"

TEST(dswap, test_base) {
	double dx1[]={-1.0}, dx11[]={-1.0},dx21[]={1.0},
		   dx2[]={1.0,-3.0},dx12[]={1.0,-3.0},dx22[]={-2.0,-2.0},
		   dx3[]={-1.0,-2.0,-3.0},dx13[]={-1.0,-2.0,-3.0},dx23[]={-1.0,0.0,5.0},
		   dx4[]={11.0,-2.0,1.0,-3.0},dx14[]={11.0,-2.0,1.0,-3.0}, dx24[]={2.0,-2.0,-1.0,1.0};

	dswap(1,dx11,dx21);
	dswap(2,dx12,dx22);
	dswap(3,dx13,dx23);
	dswap(4,dx14,dx24);

    for (int i=0; i<1; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dx21[i],dx1[i]);
	}
    for (int i=0; i<2; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dx22[i],dx2[i]);
	}
    for (int i=0; i<3; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dx23[i],dx3[i]);
	}
    for (int i=0; i<4; i++) {
	    SCOPED_TRACE(i);
	    ASSERT_EQ(dx24[i],dx4[i]);
	}
}