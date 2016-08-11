//
//  BCGFC.h
//  
//
//  Created by Sourgroup on 6/30/16.
//
//

#ifndef BCGFC_h
#define BCGFC_h

#include <stdio.h>
struct bignumber{
    double v;
    int h;
};
struct tb{
    double T;
    int B;
};
struct co{
    struct bignumber con;
    struct bignumber y;
};
struct poly{
    int order;
    struct co v[1201];
};
extern struct poly q;
extern struct poly base;
extern struct poly q0[24];

struct bignumber zb();
struct co zc() ;
struct poly zp();
struct bignumber add ( struct bignumber a, struct bignumber b);
struct bignumber mult (struct bignumber a, struct bignumber b);
struct co coadd(struct co a,struct co b);
struct bignumber by (int b, int i,double t);
struct bignumber cb (int b,int a);
struct bignumber gen(double r,int n);
int cmpl(struct bignumber a, struct bignumber b);
struct poly poadd(struct poly a,struct poly b);
struct poly polmult(struct poly a,struct poly b);
#endif /* BCGFC_h */
