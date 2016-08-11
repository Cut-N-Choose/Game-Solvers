//
//  BCGFC.c
//  
//
//  Created by Sourgroup on 6/30/16.
//
//

#include "BCGFC.h"
struct bignumber zb()
{
    struct bignumber r;
    r.v=0.0;
    r.h=0;
    return r;
};
struct co zc() //coefficient reset
{
    struct co result;
    result.con=zb();
    result.y=zb();
    return result;
};
struct poly zp() //poly reset
{
    struct poly result;
    int i;
    for(i=0;i<=1200;i++)
        result.v[i]=zc();
        return result;
    
};
double e(double v,int h,double t) //compute v*t^h
{
    int i=0;
    for(;i<h;i++)
        v=v*t;
    return v;
}
struct bignumber add ( struct bignumber a, struct bignumber b)//bignumber addition
{
    if ((b.v==0)||((a.v>0)&&(a.h-b.h>16))) return a;
    if ((a.v==0)||((b.v>0)&&(b.h-a.h>16))) return b;
    else{
        struct bignumber result;
        result=zb();
        if (a.h>b.h)
            result.v=a.v+e(b.v,a.h-b.h,0.1);
        else result.v=b.v+e(a.v,b.h-a.h,0.1);
        result.h=a.h>b.h?a.h:b.h;
        if (result.v>=1){result.v=result.v/10; result.h++;}
        return result;
    }
};
struct bignumber mult (struct bignumber a, struct bignumber b) //bignumber multiply
{
    struct bignumber result;
    result=zb();
    if(a.v*b.v==0) return result;
    if (a.v*b.v>0.1)
    {
        result.v=a.v*b.v;
        result.h=a.h+b.h;
    }
    else {
        result.v=a.v*10*b.v;
        result.h=a.h+b.h-1;
    }
    return result;
};
struct co coadd(struct co a,struct co b) //coeffient addition
{
    struct co result;
    result=zc();
    result.con=add(a.con,b.con);
    result.y=add(a.y,b.y);
    return result;
};
struct co comult(struct co b,struct co a) //coeffient multiply
{
    struct co result;
    result=zc();
    result.con=mult(a.con,b.con);
    result.y=add(add(mult(a.con,b.y),mult(a.y,b.con)),mult(a.y,b.y));
    return result;
};

struct poly pocomult(struct poly a,struct co b,int n)  // a poly multiply a cofficient
{
    struct poly result;
    result=zp();
    int i=0;
    for(;(i+n<=1200)&&(i<=a.order);i++)
        result.v[n+i]=comult(a.v[i],b);
        if (a.order+n>1200) result.order=1200;
            else result.order=a.order+n;
                return result;
};

struct poly poadd(struct poly a,struct poly b) //poly addition
{
    struct poly result;
    result=zp();
    int i=0;
    for (;(i<=1200)&&((i<=a.order)||(i<=b.order));i++)
        result.v[i]=coadd(a.v[i],b.v[i]);
        result.order=(a.order>b.order)?a.order:b.order;
        return result;
}
struct poly polmult(struct poly a,struct poly b) //ploy multiply
{
    struct poly result;
    result=zp();
    int i=0,j=0;
    for(;(j<=1200)&(j<=b.order);j++)
        result=poadd(result,pocomult(a,b.v[j],j));
        result.order=a.order+b.order>1200?1200:a.order+b.order;
        return (result);
};
struct bignumber cb (int b,int a) //compute (a choose b)
{
    struct bignumber result;
    result=zb();
    if (a<b) return result;
    if (b>a/2) b=a-b;
        result.v=0.1;
        result.h=1;
        int i=0;
        for(i=0;i<b;i++)
        {
            while (result.v*(a-i)/(i+1)>=1){result.v=result.v/10;result.h++;}
            while ((result.v*(a-i)/(i+1)<0.1)){result.v=result.v*10;result.h--;}
            result.v=result.v*(a-i)/(i+1);
        }
    return result;
};

struct bignumber gen(double r,int n) //compute r^n
{
    struct bignumber result;
    result=zb();
    result.v=0.1;
    result.h=1;
    if (n==0) return result;
    if (r==0) {result.v=0;result.h=0;return result;}
    int i;
    for(i=0;i<n;i++)
    {
        if(result.v*r<0.1){result.v=result.v*10;result.h--;}
        result.v=result.v*r;
    }
    return result;
};

struct bignumber by (int b, int i,double t) //compute t^i*(1-t)^{b-i}
{
    struct bignumber result;
    result=zb();
    result.v=0.1;
    result.h=1;
    int j=0;
    for(;j<i;j++)
    {
        if(result.v*t<0.1){result.v=result.v*10;result.h--;}
        result.v=result.v*t;
    }
    for(j=0;j<b-i;j++)
    {
        if(result.v*(1-t)<0.1){result.v=result.v*10;result.h--;}
        result.v=result.v*(1-t);
    }
    return result;
};
int cmpl(struct bignumber a, struct bignumber b) //is a>b?
{
    if(a.v==0) return 0;
    if(b.v==0) return 1;
    if((a.h>b.h)||((a.h==b.h)&&(a.v>b.v))) return 1; else return 0;
}