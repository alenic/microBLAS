#include "gtest/gtest.h"
#include "microBLAS.h"

TEST(test_dot, test_base) {
    RealType dx11[]={-1.0},dx21[]={1.0}, dexp1 = -1.0,
           dx12[]={1.0,-3.0},dx22[]={-2.0,-2.0}, dexp2 = 4.0,
           dx13[]={-1.0,-2.0,-3.0},dx23[]={-1.0,0.0,5.0}, dexp3=-14.0,
           dx14[]={11.0,-2.0,1.0,-3.0}, dx24[]={2.0,-2.0,-1.0,1.0}, dexp4=22.0;

    double eps = 1e-16;
    
    ASSERT_NEAR(dot(1,dx11,dx21), dexp1, eps);
    ASSERT_NEAR(dot(2,dx12,dx22), dexp2, eps);
    ASSERT_NEAR(dot(3,dx13,dx23), dexp3, eps);
    ASSERT_NEAR(dot(4,dx14,dx24), dexp4, eps);

}