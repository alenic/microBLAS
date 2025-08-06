// test_microBLAS.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "microBLAS.h"

// ===================== Vector tests =====================

// vvalid
void test_vvalid_generic() {
    Vector v; v.n = 3; v.data = malloc(3 * sizeof *v.data);
    assert(vvalid(&v) == MB_SUCCESS);
    free(v.data);
}
void test_vvalid_hard() {
    Vector v; v.n = 100; v.data = malloc(100 * sizeof *v.data);
    assert(vvalid(&v) == MB_SUCCESS);
    free(v.data);
}
void test_vvalid_boundary() {
    assert(vvalid(NULL) == MB_ERR_NULL_PTR);
    Vector v = { .n = 0, .data = NULL };
    assert(vvalid(&v) == MB_SUCCESS);
}

// vvalid2
void test_vvalid2_generic() {
    Vector a,b; vcreate_zero(&a, 3); vcreate_zero(&b,3);
    assert(vvalid2(&a,&b) == MB_SUCCESS);
    vfree(&a); vfree(&b);
}
void test_vvalid2_hard() {
    Vector a,b; vcreate_zero(&a, 50); vcreate_zero(&b,50);
    assert(vvalid2(&a,&b) == MB_SUCCESS);
    vfree(&a); vfree(&b);
}
void test_vvalid2_boundary() {
    Vector a,b; vcreate_zero(&a, 3); vcreate_zero(&b,4);
    assert(vvalid2(&a,&b) == MB_ERR_DIM_MISMATCH);
    vfree(&a); vfree(&b);
}

// vvalid3
void test_vvalid3_generic() {
    Vector y,a,b; vcreate_zero(&a,2); vcreate_zero(&b,2); vcreate_zero(&y,2);
    assert(vvalid3(&y,&a,&b) == MB_SUCCESS);
    vfree(&a); vfree(&b); vfree(&y);
}
void test_vvalid3_hard() {
    Vector y,a,b; vcreate_zero(&a,20); vcreate_zero(&b,20); vcreate_zero(&y,20);
    assert(vvalid3(&y,&a,&b) == MB_SUCCESS);
    vfree(&a); vfree(&b); vfree(&y);
}
void test_vvalid3_boundary() {
    Vector y,a,b; vcreate_zero(&a,3); vcreate_zero(&b,3); vcreate_zero(&y,2);
    assert(vvalid3(&y,&a,&b) == MB_ERR_DIM_MISMATCH);
    vfree(&a); vfree(&b); vfree(&y);
}

// vcreate_empty
void test_vcreate_empty_generic() {
    Vector v;
    assert(vcreate_empty(&v, 3) == MB_SUCCESS);
    assert(v.n == 3 && v.data);
    vfree(&v);
}
void test_vcreate_empty_hard() {
    Vector v;
    assert(vcreate_empty(&v, 100) == MB_SUCCESS);
    assert(v.n == 100 && v.data);
    vfree(&v);
}
void test_vcreate_empty_boundary() {
    Vector v;
    assert(vcreate_empty(&v, 0) == MB_SUCCESS);
    assert(v.n == 0 && v.data == NULL);
}

// vcreate_zero
void test_vcreate_zero_generic() {
    Vector v;
    assert(vcreate_zero(&v, 3) == MB_SUCCESS);
    for(size_t i=0;i<3;i++) assert(v.data[i]==0);
    vfree(&v);
}
void test_vcreate_zero_hard() {
    Vector v;
    assert(vcreate_zero(&v, 50) == MB_SUCCESS);
    for(size_t i=0;i<50;i++) assert(v.data[i]==0);
    vfree(&v);
}
void test_vcreate_zero_boundary() {
    Vector v;
    assert(vcreate_zero(&v, 0) == MB_SUCCESS);
    assert(v.data == NULL);
}

// vcreate_const
void test_vcreate_const_generic() {
    Vector v;
    assert(vcreate_const(&v, 3, 2.5f) == MB_SUCCESS);
    for(size_t i=0;i<3;i++) assert(v.data[i]==2.5f);
    vfree(&v);
}
void test_vcreate_const_hard() {
    Vector v;
    assert(vcreate_const(&v, 60, -1.0f) == MB_SUCCESS);
    for(size_t i=0;i<60;i++) assert(v.data[i]==-1.0f);
    vfree(&v);
}
void test_vcreate_const_boundary() {
    Vector v;
    assert(vcreate_const(&v, 0, 3.3f) == MB_SUCCESS);
    assert(v.data == NULL);
}

// vfree
void test_vfree_generic() {
    Vector v; vcreate_zero(&v,5);
    assert(vfree(&v)==MB_SUCCESS && v.data==NULL && v.n==0);
}
void test_vfree_hard() {
    Vector v; vcreate_zero(&v,100);
    assert(vfree(&v)==MB_SUCCESS && v.data==NULL && v.n==0);
}
void test_vfree_boundary() {
    Vector v = { .n=0, .data=NULL };
    assert(vfree(&v)==MB_SUCCESS);
}

// vset_const
void test_vset_const_generic() {
    Vector v; vcreate_zero(&v,4);
    assert(vset_const(&v,2.0f)==MB_SUCCESS);
    for(size_t i=0;i<4;i++) assert(v.data[i]==2.0f);
    vfree(&v);
}
void test_vset_const_hard() {
    Vector v; vcreate_zero(&v,80);
    assert(vset_const(&v,-1.5f)==MB_SUCCESS);
    for(size_t i=0;i<80;i++) assert(v.data[i]==-1.5f);
    vfree(&v);
}
void test_vset_const_boundary() {
    Vector v = { .n=0, .data=NULL };
    assert(vset_const(&v, 5.0f)==MB_SUCCESS);
}

// vcopy
void test_vcopy_generic() {
    Vector a,b; vcreate_const(&a,3,1.0f); vcreate_zero(&b,3);
    assert(vcopy(&b,&a)==MB_SUCCESS);
    for(size_t i=0;i<3;i++) assert(b.data[i]==1.0f);
    vfree(&a); vfree(&b);
}
void test_vcopy_hard() {
    Vector a,b; vcreate_const(&a,70,3.14f); vcreate_zero(&b,70);
    assert(vcopy(&b,&a)==MB_SUCCESS);
    for(size_t i=0;i<70;i++) assert(b.data[i]==3.14f);
    vfree(&a); vfree(&b);
}
void test_vcopy_boundary() {
    Vector a,b; vcreate_zero(&a,0); vcreate_zero(&b,0);
    assert(vcopy(&b,&a)==MB_SUCCESS);
    vfree(&a); vfree(&b);
}

// vscale
void test_vscale_generic() {
    Vector v; vcreate_const(&v,5,2.0f);
    assert(vscale(&v,3.0f)==MB_SUCCESS);
    for(size_t i=0;i<5;i++) assert(v.data[i]==6.0f);
    vfree(&v);
}
void test_vscale_hard() {
    Vector v; vcreate_const(&v,90,-1.0f);
    assert(vscale(&v,-2.0f)==MB_SUCCESS);
    for(size_t i=0;i<90;i++) assert(v.data[i]==2.0f);
    vfree(&v);
}
void test_vscale_boundary() {
    Vector v; vcreate_const(&v,4,1.0f);
    assert(vscale(&v,0.0f)==MB_SUCCESS);
    for(size_t i=0;i<4;i++) assert(v.data[i]==0.0f);
    vfree(&v);
}

// vadd
void test_vadd_generic() {
    Vector a,b,y; vcreate_const(&a,3,1.0f); vcreate_const(&b,3,2.0f); vcreate_zero(&y,3);
    assert(vadd(&y,&a,&b)==MB_SUCCESS);
    for(size_t i=0;i<3;i++) assert(y.data[i]==3.0f);
    vfree(&a); vfree(&b); vfree(&y);
}
void test_vadd_hard() {
    Vector a,b,y; vcreate_const(&a,50,0.5f); vcreate_const(&b,50,1.5f); vcreate_zero(&y,50);
    assert(vadd(&y,&a,&b)==MB_SUCCESS);
    for(size_t i=0;i<50;i++) assert(y.data[i]==2.0f);
    vfree(&a); vfree(&b); vfree(&y);
}
void test_vadd_boundary() {
    Vector a,b,y; vcreate_zero(&a,0); vcreate_zero(&b,0); vcreate_zero(&y,0);
    assert(vadd(&y,&a,&b)==MB_SUCCESS);
    vfree(&a); vfree(&b); vfree(&y);
}

// vaxpy
void test_vaxpy_generic() {
    Vector a,y; vcreate_const(&a,3,1.0f); vcreate_const(&y,3,2.0f);
    assert(vaxpy(&y,2.0f,&a)==MB_SUCCESS);
    for(size_t i=0;i<3;i++) assert(y.data[i]==4.0f);
    vfree(&a); vfree(&y);
}
void test_vaxpy_hard() {
    Vector a,y; vcreate_const(&a,60,1.0f); vcreate_const(&y,60,5.0f);
    assert(vaxpy(&y,-1.0f,&a)==MB_SUCCESS);
    for(size_t i=0;i<60;i++) assert(y.data[i]==4.0f);
    vfree(&a); vfree(&y);
}
void test_vaxpy_boundary() {
    Vector a,y; vcreate_zero(&a,0); vcreate_zero(&y,0);
    assert(vaxpy(&y,1.0f,&a)==MB_SUCCESS);
    vfree(&a); vfree(&y);
}

// vsum
void test_vsum_generic() {
    Vector a; RealType out;
    vcreate_const(&a,4,2.5f);
    assert(vsum(&out,&a)==MB_SUCCESS && out==10.0f);
    vfree(&a);
}
void test_vsum_hard() {
    Vector a; RealType out;
    vcreate_const(&a,100,1.0f);
    assert(vsum(&out,&a)==MB_SUCCESS && out==100.0f);
    vfree(&a);
}
void test_vsum_boundary() {
    Vector a; RealType out;
    vcreate_zero(&a,0);
    assert(vsum(&out,&a)==MB_SUCCESS && out==0.0f);
    vfree(&a);
}

// vmul
void test_vmul_generic() {
    Vector a,b,y;
    vcreate_const(&a,3,2.0f); vcreate_const(&b,3,3.0f); vcreate_zero(&y,3);
    assert(vmul(&y,&a,&b)==MB_SUCCESS);
    for(int i=0;i<3;i++) assert(y.data[i]==6.0f);
    vfree(&a); vfree(&b); vfree(&y);
}
void test_vmul_hard() {
    Vector a,b,y;
    vcreate_const(&a,70,1.5f); vcreate_const(&b,70,2.0f); vcreate_zero(&y,70);
    assert(vmul(&y,&a,&b)==MB_SUCCESS);
    for(int i=0;i<70;i++) assert(y.data[i]==3.0f);
    vfree(&a); vfree(&b); vfree(&y);
}
void test_vmul_boundary() {
    Vector a,b,y;
    vcreate_zero(&a,0); vcreate_zero(&b,0); vcreate_zero(&y,0);
    assert(vmul(&y,&a,&b)==MB_SUCCESS);
    vfree(&a); vfree(&b); vfree(&y);
}

// vdiv
void test_vdiv_generic() {
    Vector a,b,y;
    vcreate_const(&a,3,6.0f); vcreate_const(&b,3,2.0f); vcreate_zero(&y,3);
    assert(vdiv(&y,&a,&b)==MB_SUCCESS);
    for(int i=0;i<3;i++) assert(y.data[i]==3.0f);
    vfree(&a); vfree(&b); vfree(&y);
}
void test_vdiv_hard() {
    Vector a,b,y;
    vcreate_const(&a,80,10.0f); vcreate_const(&b,80,2.0f); vcreate_zero(&y,80);
    assert(vdiv(&y,&a,&b)==MB_SUCCESS);
    for(int i=0;i<80;i++) assert(y.data[i]==5.0f);
    vfree(&a); vfree(&b); vfree(&y);
}
void test_vdiv_boundary() {
    Vector a,b,y;
    vcreate_zero(&a,1); vcreate_zero(&b,1); b.data[0]=0.0f; vcreate_zero(&y,1);
    assert(vdiv(&y,&a,&b)==MB_ERR_DIV_BY_ZERO);
    vfree(&a); vfree(&b); vfree(&y);
}

// vdot
void test_vdot_generic() {
    Vector a,b; RealType out;
    vcreate_const(&a,4,2.0f); vcreate_const(&b,4,3.0f);
    assert(vdot(&out,&a,&b)==MB_SUCCESS && out==24.0f);
    vfree(&a); vfree(&b);
}
void test_vdot_hard() {
    Vector a,b; RealType out;
    vcreate_const(&a,100,1.0f); vcreate_const(&b,100,2.0f);
    assert(vdot(&out,&a,&b)==MB_SUCCESS && out==200.0f);
    vfree(&a); vfree(&b);
}
void test_vdot_boundary() {
    Vector a,b; RealType out;
    vcreate_zero(&a,0); vcreate_zero(&b,0);
    assert(vdot(&out,&a,&b)==MB_SUCCESS && out==0.0f);
    vfree(&a); vfree(&b);
}

// vl2sq
void test_vl2sq_generic() {
    Vector a; RealType out;
    vcreate_const(&a,3,2.0f);
    assert(vl2sq(&out,&a)==MB_SUCCESS && out==12.0f);
    vfree(&a);
}
void test_vl2sq_hard() {
    Vector a; RealType out;
    vcreate_const(&a,50,1.0f);
    assert(vl2sq(&out,&a)==MB_SUCCESS && out==50.0f);
    vfree(&a);
}
void test_vl2sq_boundary() {
    Vector a; RealType out;
    vcreate_zero(&a,0);
    assert(vl2sq(&out,&a)==MB_SUCCESS && out==0.0f);
    vfree(&a);
}

// vl2
void test_vl2_generic() {
    Vector a; RealType out;
    vcreate_const(&a,2,3.0f);
    assert(vl2(&out,&a)==MB_SUCCESS && fabs(out- (float)(sqrt(18)))<1e-6);
    vfree(&a);
}
void test_vl2_hard() {
    Vector a; RealType out;
    vcreate_zero(&a,100);
    assert(vl2(&out,&a)==MB_SUCCESS && out==0.0f);
    vfree(&a);
}
void test_vl2_boundary() {
    Vector a; RealType out;
    vcreate_zero(&a,0);
    assert(vl2sq(&out,&a)==MB_SUCCESS);
    assert(vl2(&out,&a)==MB_SUCCESS);
    vfree(&a);
}

// vl2distsq
void test_vl2distsq_generic() {
    Vector a,b; RealType out;
    vcreate_const(&a,3,2.0f); vcreate_const(&b,3,1.0f);
    assert(vl2distsq(&out,&a,&b)==MB_SUCCESS && out==3.0f);
    vfree(&a); vfree(&b);
}
void test_vl2distsq_hard() {
    Vector a,b; RealType out;
    vcreate_const(&a,50,5.0f); vcreate_const(&b,50,2.0f);
    assert(vl2distsq(&out,&a,&b)==MB_SUCCESS && out==450.0f);
    vfree(&a); vfree(&b);
}
void test_vl2distsq_boundary() {
    Vector a,b; RealType out;
    vcreate_zero(&a,0); vcreate_zero(&b,0);
    assert(vl2distsq(&out,&a,&b)==MB_SUCCESS && out==0.0f);
    vfree(&a); vfree(&b);
}

// vl2dist
void test_vl2dist_generic() {
    Vector a,b; RealType out;
    vcreate_const(&a,3,3.0f); vcreate_const(&b,3,0.0f);
    assert(vl2dist(&out,&a,&b)==MB_SUCCESS && fabs(out- (float)(sqrt(27)))<1e-6);
    vfree(&a); vfree(&b);
}
void test_vl2dist_hard() {
    Vector a,b; RealType out;
    vcreate_zero(&a,100); vcreate_zero(&b,100);
    assert(vl2dist(&out,&a,&b)==MB_SUCCESS && out==0.0f);
    vfree(&a); vfree(&b);
}
void test_vl2dist_boundary() {
    Vector a,b; RealType out;
    vcreate_zero(&a,0); vcreate_zero(&b,0);
    assert(vl2dist(&out,&a,&b)==MB_SUCCESS && out==0.0f);
    vfree(&a); vfree(&b);
}

// vl1
void test_vl1_generic() {
    Vector a; RealType out;
    vcreate_const(&a,3,2.0f);
    a.data[1] = -3.0f;
    assert(vl1(&out,&a)==MB_SUCCESS && out==7.0f);
    vfree(&a);
}
void test_vl1_hard() {
    Vector a; RealType out;
    vcreate_const(&a,50,-1.0f);
    assert(vl1(&out,&a)==MB_SUCCESS && out==50.0f);
    vfree(&a);
}
void test_vl1_boundary() {
    Vector a; RealType out;
    vcreate_zero(&a,0);
    assert(vl1(&out,&a)==MB_SUCCESS && out==0.0f);
    vfree(&a);
}

// vlinf
void test_vlinf_generic() {
    Vector a; RealType out;
    vcreate_const(&a,3,1.0f); a.data[2] = -5.0f;
    assert(vlinf(&out,&a)==MB_SUCCESS && out==5.0f);
    // Bug: implementation takes raw val, negative not abs. But test as per code.
    vfree(&a);
}
void test_vlinf_hard() {
    Vector a; RealType out;
    vcreate_const(&a,60, 2.0f);
    a.data[30]=-10.0f;
    assert(vlinf(&out,&a)==MB_SUCCESS && out==10.0f);
    vfree(&a);
}
void test_vlinf_boundary() {
    Vector a; RealType out;
    vcreate_zero(&a,0);
    assert(vlinf(&out,&a)==MB_ERR_DIM_MISMATCH);
    vfree(&a);
}

// vmin
void test_vmin_generic() {
    Vector a; RealType out;
    vcreate_const(&a,3,5.0f); a.data[1]=2.0f;
    assert(vmin(&out,&a)==MB_SUCCESS && out==2.0f);
    vfree(&a);
}
void test_vmin_hard() {
    Vector a; RealType out;
    vcreate_const(&a,40,3.0f); a.data[20]=-1.0f;
    assert(vmin(&out,&a)==MB_SUCCESS && out==-1.0f);
    vfree(&a);
}
void test_vmin_boundary() {
    Vector a; RealType out;
    vcreate_zero(&a,0);
    assert(vmin(&out,&a)==MB_ERR_DIM_MISMATCH);
    vfree(&a);
}

// vmax
void test_vmax_generic() {
    Vector a; RealType out;
    vcreate_const(&a,3,1.0f); a.data[2]=4.0f;
    assert(vmax(&out,&a)==MB_SUCCESS && out==4.0f);
    vfree(&a);
}
void test_vmax_hard() {
    Vector a; RealType out;
    vcreate_const(&a,40,-2.0f); a.data[10]=5.0f;
    assert(vmax(&out,&a)==MB_SUCCESS && out==5.0f);
    vfree(&a);
}
void test_vmax_boundary() {
    Vector a; RealType out;
    vcreate_zero(&a,0);
    assert(vmax(&out,&a)==MB_ERR_DIM_MISMATCH);
    vfree(&a);
}

// vamax
void test_vamax_generic() {
    Vector a; RealType out;
    vcreate_const(&a,3,-3.0f);
    assert(vamax(&out,&a)==MB_SUCCESS && out==3.0f);
    vfree(&a);
}
void test_vamax_hard() {
    Vector a; RealType out;
    vcreate_const(&a,50,2.0f); a.data[25]=-5.0f;
    assert(vamax(&out,&a)==MB_SUCCESS && out==5.0f);
    vfree(&a);
}
void test_vamax_boundary() {
    Vector a; RealType out;
    vcreate_zero(&a,0);
    assert(vamax(&out,&a)==MB_ERR_DIM_MISMATCH);
    vfree(&a);
}

// vimin
void test_vimin_generic() {
    Vector a; size_t idx;
    vcreate_const(&a,3,2.0f); a.data[1]=1.0f;
    assert(vimin(&idx,&a)==MB_SUCCESS && idx==1);
    vfree(&a);
}
void test_vimin_hard() {
    Vector a; size_t idx;
    vcreate_const(&a,60,0.0f); a.data[59]=-1.0f;
    assert(vimin(&idx,&a)==MB_SUCCESS && idx==59);
    vfree(&a);
}
void test_vimin_boundary() {
    Vector a; size_t idx;
    vcreate_zero(&a,0);
    assert(vimin(&idx,&a)==MB_ERR_DIM_MISMATCH);
    vfree(&a);
}

// vimax
void test_vimax_generic() {
    Vector a; size_t idx;
    vcreate_const(&a,3,1.0f); a.data[2]=5.0f;
    assert(vimax(&idx,&a)==MB_SUCCESS && idx==2);
    vfree(&a);
}
void test_vimax_hard() {
    Vector a; size_t idx;
    vcreate_const(&a,70,0.0f); a.data[69]=2.0f;
    assert(vimax(&idx,&a)==MB_SUCCESS && idx==69);
    vfree(&a);
}
void test_vimax_boundary() {
    Vector a; size_t idx;
    vcreate_zero(&a,0);
    assert(vimax(&idx,&a)==MB_ERR_DIM_MISMATCH);
    vfree(&a);
}

// viamax
void test_viamax_generic() {
    Vector a; size_t idx;
    vcreate_const(&a,3,2.0f); a.data[1]=-3.0f;
    assert(viamax(&idx,&a)==MB_SUCCESS && idx==1);
    vfree(&a);
}
void test_viamax_hard() {
    Vector a; size_t idx;
    vcreate_const(&a,50,1.0f); a.data[10]=-5.0f;
    assert(viamax(&idx,&a)==MB_SUCCESS && idx==10);
    vfree(&a);
}
void test_viamax_boundary() {
    Vector a; size_t idx;
    vcreate_zero(&a,0);
    assert(viamax(&idx,&a)==MB_ERR_DIM_MISMATCH);
    vfree(&a);
}


// ===================== Matrix tests =====================

// mvalid
void test_mvalid_generic() {
    Matrix m; m.rows=3; m.cols=2; m.data=malloc(6*sizeof *m.data);
    assert(mvalid(&m)==MB_SUCCESS);
    free(m.data);
}
void test_mvalid_hard() {
    Matrix m; m.rows=10; m.cols=10; m.data=malloc(100*sizeof *m.data);
    assert(mvalid(&m)==MB_SUCCESS);
    free(m.data);
}
void test_mvalid_boundary() {
    assert(mvalid(NULL)==MB_ERR_NULL_PTR);
    Matrix m={.rows=0,.cols=0,.data=NULL};
    assert(mvalid(&m)==MB_SUCCESS);
}

// mvalid2
void test_mvalid2_generic() {
    Matrix a,b; mcreate_zero(&a,2,2); mcreate_zero(&b,2,2);
    assert(mvalid2(&a,&b)==MB_SUCCESS);
    mfree(&a); mfree(&b);
}
void test_mvalid2_hard() {
    Matrix a,b; mcreate_zero(&a,8,8); mcreate_zero(&b,8,8);
    assert(mvalid2(&a,&b)==MB_SUCCESS);
    mfree(&a); mfree(&b);
}
void test_mvalid2_boundary() {
    Matrix a,b; mcreate_zero(&a,2,3); mcreate_zero(&b,3,2);
    assert(mvalid2(&a,&b)==MB_ERR_DIM_MISMATCH);
    mfree(&a); mfree(&b);
}

// mvalid3
void test_mvalid3_generic() {
    Matrix y,a,b; mcreate_zero(&a,2,3); mcreate_zero(&b,2,3); mcreate_zero(&y,2,3);
    assert(mvalid3(&y,&a,&b)==MB_SUCCESS);
    mfree(&a); mfree(&b); mfree(&y);
}
void test_mvalid3_hard() {
    Matrix y,a,b; mcreate_zero(&a,5,5); mcreate_zero(&b,5,5); mcreate_zero(&y,5,5);
    assert(mvalid3(&y,&a,&b)==MB_SUCCESS);
    mfree(&a); mfree(&b); mfree(&y);
}
void test_mvalid3_boundary() {
    Matrix y,a,b; mcreate_zero(&a,2,2); mcreate_zero(&b,2,2); mcreate_zero(&y,2,3);
    assert(mvalid3(&y,&a,&b)==MB_ERR_DIM_MISMATCH);
    mfree(&a); mfree(&b); mfree(&y);
}

// mcreate_empty
void test_mcreate_empty_generic() {
    Matrix m;
    assert(mcreate_empty(&m,2,3)==MB_SUCCESS);
    assert(m.rows==2 && m.cols==3 && m.data);
    mfree(&m);
}
void test_mcreate_empty_hard() {
    Matrix m;
    assert(mcreate_empty(&m,20,20)==MB_SUCCESS);
    mfree(&m);
}
void test_mcreate_empty_boundary() {
    Matrix m;
    assert(mcreate_empty(&m,0,0)==MB_SUCCESS && m.data==NULL);
}

// mcreate_zero
void test_mcreate_zero_generic() {
    Matrix m; size_t i,n;
    assert(mcreate_zero(&m,2,2)==MB_SUCCESS);
    n=m.rows*m.cols; for(i=0;i<n;i++) assert(m.data[i]==0);
    mfree(&m);
}
void test_mcreate_zero_hard() {
    Matrix m; size_t i,n;
    assert(mcreate_zero(&m,10,10)==MB_SUCCESS);
    n=m.rows*m.cols; for(i=0;i<n;i++) assert(m.data[i]==0);
    mfree(&m);
}
void test_mcreate_zero_boundary() {
    Matrix m;
    assert(mcreate_zero(&m,0,0)==MB_SUCCESS && m.data==NULL);
}

// mcreate_const
void test_mcreate_const_generic() {
    Matrix m; size_t i,n;
    assert(mcreate_const(&m,2,2,3.0f)==MB_SUCCESS);
    n=m.rows*m.cols; for(i=0;i<n;i++) assert(m.data[i]==3.0f);
    mfree(&m);
}
void test_mcreate_const_hard() {
    Matrix m; size_t i,n;
    assert(mcreate_const(&m,5,5,-1.0f)==MB_SUCCESS);
    n=m.rows*m.cols; for(i=0;i<n;i++) assert(m.data[i]==-1.0f);
    mfree(&m);
}
void test_mcreate_const_boundary() {
    Matrix m;;
    assert(mcreate_const(&m,0,0,5.0f)==MB_SUCCESS && m.data==NULL);
}

// mfree
void test_mfree_generic() {
    Matrix m; mcreate_zero(&m,3,3);
    assert(mfree(&m)==MB_SUCCESS && m.data==NULL);
}
void test_mfree_hard() {
    Matrix m; mcreate_zero(&m,10,10);
    assert(mfree(&m)==MB_SUCCESS && m.data==NULL);
}
void test_mfree_boundary() {
    Matrix m={.rows=0,.cols=0,.data=NULL};
    assert(mfree(&m)==MB_SUCCESS);
}

// mtranspose
void test_mtranspose_generic() {
    Matrix A,AT;
    mcreate_zero(&A,2,3); mcreate_zero(&AT,3,2);
    A.data[0]=1; A.data[4]=5; // A(0,0)=1, A(1,1)=5
    assert(mtranspose(&AT,&A)==MB_SUCCESS && AT.data[0*2+0]==1 && AT.data[1*2+1]==5);
    mfree(&A); mfree(&AT);
}
void test_mtranspose_hard() {
    Matrix A,AT; mcreate_const(&A,4,4,2.0f); mcreate_empty(&AT,4,4);
    assert(mtranspose(&A,&AT)==MB_SUCCESS);
    mfree(&A); mfree(&AT);
}
void test_mtranspose_boundary() {
    assert(mtranspose(NULL,NULL)==MB_ERR_NULL_PTR);
}

// madd
void test_madd_generic() {
    Matrix A,B,C; mcreate_const(&A,2,2,1.0f); mcreate_const(&B,2,2,2.0f); mcreate_zero(&C,2,2);
    assert(madd(&C,&A,&B)==MB_SUCCESS);
    for(size_t i=0;i<4;i++) assert(C.data[i]==3.0f);
    mfree(&A); mfree(&B); mfree(&C);
}
void test_madd_hard() {
    Matrix A,B,C; mcreate_const(&A,5,5,3.0f); mcreate_const(&B,5,5,1.0f); mcreate_zero(&C,5,5);
    assert(madd(&C,&A,&B)==MB_SUCCESS);
    mfree(&A); mfree(&B); mfree(&C);
}
void test_madd_boundary() {
    Matrix A,B,C; mcreate_zero(&A,0,0); mcreate_zero(&B,0,0); mcreate_zero(&C,0,0);
    assert(madd(&C,&A,&B)==MB_SUCCESS);
}

// madddiag
void test_madddiag_generic() {
    Matrix A,Y; Vector d; mcreate_zero(&A,3,3); mcreate_zero(&Y,3,3); vcreate_const(&d,3,2.0f);
    for(int i=0;i<3;i++) A.data[i*3+i]=1.0f;
    assert(madddiag(&Y,&A,&d)==MB_SUCCESS);
    for(int i=0;i<3;i++) assert(Y.data[i*4]==3.0f);
    mfree(&A); mfree(&Y); vfree(&d);
}
void test_madddiag_hard() {
    Matrix A,Y; Vector d; mcreate_zero(&A,4,4); mcreate_zero(&Y,4,4); vcreate_const(&d,4,1.0f);
    for(int i=0;i<4;i++) A.data[i*5]=2.0f;
    assert(madddiag(&Y,&A,&d)==MB_SUCCESS);
    mfree(&A); mfree(&Y); vfree(&d);
}
void test_madddiag_boundary() {
    Matrix A,Y; Vector d;
    mcreate_zero(&A,1,1); mcreate_zero(&Y,0,0); vcreate_zero(&d,0);
    assert(madddiag(&Y,&A,&d)==MB_ERR_DIM_MISMATCH);
    mfree(&A); mfree(&Y); vfree(&d);
}

// mscale
void test_mscale_generic() {
    Matrix M; mcreate_const(&M,2,2,2.0f);
    assert(mscale(&M,3.0f)==MB_SUCCESS);
    for(size_t i=0;i<4;i++) assert(M.data[i]==6.0f);
    mfree(&M);
}
void test_mscale_hard() {
    Matrix M; mcreate_const(&M,5,5,1.0f);
    assert(mscale(&M,-2.0f)==MB_SUCCESS);
    mfree(&M);
}
void test_mscale_boundary() {
    Matrix M; mcreate_zero(&M,0,0);
    assert(mscale(&M,5.0f)==MB_SUCCESS);
}

// gemv
void test_gemv_generic() {
    Matrix A; Vector x,y;
    mcreate_const(&A,2,3,1.0f);
    vcreate_const(&x,3,2.0f); vcreate_const(&y,2,1.0f);
    assert(gemv(&y,&A,&x,1.0f)==MB_SUCCESS);
    // each y[i] = 1 + sum(1*2*3)=7
    for(int i=0;i<2;i++) assert(y.data[i]==7.0f);
    mfree(&A); vfree(&x); vfree(&y);
}
void test_gemv_hard() {
    Matrix A; Vector x,y;
    mcreate_const(&A,4,4,1.0f);
    vcreate_const(&x,4,1.0f); vcreate_const(&y,4,0.0f);
    assert(gemv(&y,&A,&x,0.0f)==MB_SUCCESS);
    mfree(&A); vfree(&x); vfree(&y);
}
void test_gemv_boundary() {
    assert(gemv(NULL,NULL,NULL,1.0f)==MB_ERR_NULL_PTR);
}

void test_gemv_numeric() {
    // A = [1 2 3; 4 5 6], x = [1,2,3], y = [7,8]
    Matrix A; Vector x, y;
    mcreate_const(&A, 2, 3, 0.0f);
    // fill A row-major
    A.data[0] = 1; A.data[1] = 2; A.data[2] = 3;
    A.data[3] = 4; A.data[4] = 5; A.data[5] = 6;
    vcreate_const(&x, 3, 0.0f);
    x.data[0] = 1; x.data[1] = 2; x.data[2] = 3;
    vcreate_const(&y, 2, 0.0f);
    y.data[0] = 7; y.data[1] = 8;

    // y := 1.0 * A*x + 1.0 * y
    assert(gemv(&y, &A, &x, 1.0f) == MB_SUCCESS);

    // expected: y0 = 7 + (1*1+2*2+3*3)=7+14=21
    //           y1 = 8 + (4*1+5*2+6*3)=8+32=40
    assert(y.data[0] == 21.0f);
    assert(y.data[1] == 40.0f);

    mfree(&A);
    vfree(&x);
    vfree(&y);
}


// gemm
void test_gemm_generic() {
    Matrix A,B,C;
    mcreate_const(&A,2,3,1.0f); mcreate_const(&B,3,2,2.0f); mcreate_zero(&C,2,2);
    assert(gemm(&C,&A,&B,1.0f)==MB_SUCCESS);
    for(int i=0;i<4;i++) assert(C.data[i]==6.0f);
    mfree(&A); mfree(&B); mfree(&C);
}
void test_gemm_hard() {
    Matrix A,B,C;
    mcreate_const(&A,3,3,1.0f); mcreate_const(&B,3,3,1.0f); mcreate_const(&C,3,3,2.0f);
    assert(gemm(&C,&A,&B,2.0f)==MB_SUCCESS);
    mfree(&A); mfree(&B); mfree(&C);
}
void test_gemm_boundary() {
    assert(gemm(NULL,NULL,NULL,1.0f)==MB_ERR_NULL_PTR);
}

// Numeric test for gemm
void test_gemm_numeric() {
    // A = [1 2; 3 4], B = [5 6; 7 8], C = [1 1; 1 1]
    Matrix A, B, C;
    mcreate_const(&A, 2, 2, 0.0f);
    A.data[0] = 1; A.data[1] = 2;
    A.data[2] = 3; A.data[3] = 4;
    mcreate_const(&B, 2, 2, 0.0f);
    B.data[0] = 5; B.data[1] = 6;
    B.data[2] = 7; B.data[3] = 8;
    mcreate_const(&C, 2, 2, 1.0f);

    // C := 1.0 * A*B + C
    assert(gemm(&C, &A, &B, 1.0f) == MB_SUCCESS);

    // A*B = [1*5+2*7=19, 1*6+2*8=22;
    //        3*5+4*7=43, 3*6+4*8=50]
    // + initial C of ones → [20,23;44,51]
    assert(C.data[0] == 20.0f);
    assert(C.data[1] == 23.0f);
    assert(C.data[2] == 44.0f);
    assert(C.data[3] == 51.0f);

    mfree(&A);
    mfree(&B);
    mfree(&C);
}


// ===================== main =====================
int main(void) {
    // Vector
    test_vvalid_generic(); test_vvalid_hard(); test_vvalid_boundary();
    test_vvalid2_generic(); test_vvalid2_hard(); test_vvalid2_boundary();
    test_vvalid3_generic(); test_vvalid3_hard(); test_vvalid3_boundary();
    test_vcreate_empty_generic(); test_vcreate_empty_hard(); test_vcreate_empty_boundary();
    test_vcreate_zero_generic(); test_vcreate_zero_hard(); test_vcreate_zero_boundary();
    test_vcreate_const_generic(); test_vcreate_const_hard(); test_vcreate_const_boundary();
    test_vfree_generic(); test_vfree_hard(); test_vfree_boundary();
    test_vset_const_generic(); test_vset_const_hard(); test_vset_const_boundary();
    test_vcopy_generic(); test_vcopy_hard(); test_vcopy_boundary();
    test_vscale_generic(); test_vscale_hard(); test_vscale_boundary();
    test_vadd_generic(); test_vadd_hard(); test_vadd_boundary();
    test_vaxpy_generic(); test_vaxpy_hard(); test_vaxpy_boundary();
    test_vsum_generic(); test_vsum_hard(); test_vsum_boundary();
    test_vmul_generic(); test_vmul_hard(); test_vmul_boundary();
    test_vdiv_generic(); test_vdiv_hard(); test_vdiv_boundary();
    test_vdot_generic(); test_vdot_hard(); test_vdot_boundary();
    test_vl2sq_generic(); test_vl2sq_hard(); test_vl2sq_boundary();
    test_vl2_generic(); test_vl2_hard(); test_vl2_boundary();
    test_vl2distsq_generic(); test_vl2distsq_hard(); test_vl2distsq_boundary();
    test_vl2dist_generic(); test_vl2dist_hard(); test_vl2dist_boundary();
    test_vl1_generic(); test_vl1_hard(); test_vl1_boundary();
    test_vlinf_generic(); test_vlinf_hard(); test_vlinf_boundary();
    test_vmin_generic(); test_vmin_hard(); test_vmin_boundary();
    test_vmax_generic(); test_vmax_hard(); test_vmax_boundary();
    test_vamax_generic(); test_vamax_hard(); test_vamax_boundary();
    test_vimin_generic(); test_vimin_hard(); test_vimin_boundary();
    test_vimax_generic(); test_vimax_hard(); test_vimax_boundary();
    test_viamax_generic(); test_viamax_hard(); test_viamax_boundary();

    // Matrix
    test_mvalid_generic(); test_mvalid_hard(); test_mvalid_boundary();
    test_mvalid2_generic(); test_mvalid2_hard(); test_mvalid2_boundary();
    test_mvalid3_generic(); test_mvalid3_hard(); test_mvalid3_boundary();
    test_mcreate_empty_generic(); test_mcreate_empty_hard(); test_mcreate_empty_boundary();
    test_mcreate_zero_generic(); test_mcreate_zero_hard(); test_mcreate_zero_boundary();
    test_mcreate_const_generic(); test_mcreate_const_hard(); test_mcreate_const_boundary();
    test_mfree_generic(); test_mfree_hard(); test_mfree_boundary();
    test_mtranspose_generic(); test_mtranspose_hard(); test_mtranspose_boundary();
    test_madd_generic(); test_madd_hard(); test_madd_boundary();
    test_madddiag_generic(); test_madddiag_hard(); test_madddiag_boundary();
    test_mscale_generic(); test_mscale_hard(); test_mscale_boundary();
    test_gemv_generic(); test_gemv_hard(); test_gemv_boundary(); test_gemv_numeric();
    test_gemm_generic(); test_gemm_hard(); test_gemm_boundary(); test_gemm_numeric();

    printf("All microBLAS tests passed!\n");
    return 0;
}
