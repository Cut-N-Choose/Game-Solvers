#include "BatchedCut.h"
int B;
int a[20];
struct poly q;
struct poly base;
struct poly q0[24];


/*
 * compute how many bits are there in the binary representing of N
 * input N
 * output number of bits
 */
int bbits(int N)
{
    int n0=0;
    do{
        int i=19;
        for(;i>0;i--)
            a[i]=a[i-1];
    a[0]=N%2;
    N=N/2;
    n0++;
}while(N>0);
return n0;
}


/*
 *  compute the generation function ((1+x)^b+(y-1)*x^b)^n
 *  Input b, n
 *  output ((1+x)^b+(y-1)*x^b)^n
 */
struct poly _compute_generation_function(int b,int n)
{
    struct poly base1;
    base1=zp();
    base1.v[0].con.v=0.1; base1.v[0].con.h=1;
    base1.v[1].con.v=0.1; base1.v[1].con.h=1;
    base1.v[0].y.v=0; base1.v[0].y.h=0;
    base1.v[1].y.v=0; base1.v[1].y.h=0;
    base1.order=1;
    base=base1;
    int i=0;
    for(i=0;i<b-1;i++)
    base=polmult(base,base1);
    base.v[b].con.v=0;
    base.v[b].con.h=0;
    base.v[b].y.v=0.1;
    base.v[b].y.h=1;
    struct poly result1;
    result1=base;
    int j;
    int end=bbits(n);
    for(j=1;j<end;j++)
    {
        result1=polmult(result1,result1);
        if (a[j]==1) result1=polmult(result1,base);
    }
    for(i=0;((i<=1200)&&(i<=n*b));i++)
    if(result1.v[i].y.v!=0){
        result1.v[i].con=add(result1.v[i].con,result1.v[i].y);
        result1.v[i].y.h=result1.v[i].y.h-result1.v[i].con.h;
        if (result1.v[i].y.v>=result1.v[i].con.v) {result1.v[i].y.v=result1.v[i].y.v/10;result1.v[i].y.h++;}
        result1.v[i].y.v=result1.v[i].y.v/result1.v[i].con.v;
    }
return result1;
}

/*
 * compute \sum_i=0^b 0.5^i*(b choose i)*t^i*(1-t)^{b-i}*q_{b-i}, where q_i=P(Fail|i bad gates in the circuit)
 *
 * return the sum
 */
struct bignumber P(int b,int s,double t)
{
    struct bignumber result;
    result=zb();
    if(b<B) return result;
    int i=0;
    for(i=0;i<=b;i++)
    {
     struct bignumber r1,r2,r3,r4,r5,r6;
     r1=gen(0.5,i);
     r2=cb(i,b);
     r3=by(b,i,t);
     r4=mult(r2,r3);
     r5=mult(r4,r1);
     r6=mult(r5,q.v[b-i].y);
    result=add(result,r6);
    }
    return result;
};

/*
 * check whetehr this (B, N, T) is secure enough, t=(T-NB)/T
 * Input: N---circuit size; B----bucket size s-----security parameter T
 * Output: 0 --- the combination is not secure, 1 --- the combination is secure
 */
int securitycheck(int N,int B,int s, double t)
{
    struct bignumber result,result1;
    result1=zb();
    result=zb();
    result.h=-1000;
    result.v=0.1;
    int i,b1=0;
    for (i=2;((i<1200)&&(i<N*B));i++)
    {
        result1=P(i,s,t);
        if(cmpl (result1,result)==1)
        {
            result=result1;
            b1=i;
        struct bignumber result3;
        result3=result;
        int j;
        for(j=0;j<s;j++)
        {
            if(result3.v*2>1){result3.v=result3.v/10;result3.h++;}
            result3.v=result3.v*2;
        }
            if ((result3.h>1)||((result3.h==1)&&(result3.v>0.1)))return 0;
        }

    }
return 1;
}


/*
 * find the best combination of (T,B)
 * Input N----size of the circuit, s---security parameter r----cost ratio
 * Output: the best combination
 */
struct tb find (int N, int s, double r)
{
    double T=-1;
    int b0=0;
    int sgn;
    int t;
    int t0;
    B=2;
    do{
    t=B*N*9;
    t0=B*N*4;
    q=q0[B-2];
    do{
        double t1;
        t1=(1.0*(t-B*N))/t;
        sgn=securitycheck(N,B,s,t1);
        if (sgn==0) t=t+t0;
        if(sgn==1) {
            if ((T>(t+(r-1)*B*N))||(T<=0))
            {
                T=t+(r-1)*B*N;
                b0=B;
            }
            t=t-t0;
        }
            t0=t0/2;
        }while(t0>1);
     B=B+1;
    }while ((T<=0)||(B*N*r<T));
    struct tb tresult;
    tresult.T=T;
    tresult.B=b0;
    return tresult;
}


void BatchedCut(int N, int s,double r)
{
    int B;
    int i,j;
    struct tb b;
    for (B=2;B<17;B++)
    {
        q0[B-2]=_compute_generation_function(B,N); //pre-compute the generation functions
    }
    b=find(N,s,r);
    printf("N=%d T=%lf B=%d\n",N,b.T-(r-1)*b.B*N,b.B);
    return;
}
