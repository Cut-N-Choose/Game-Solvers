//#include<iostream>
#include "MajorityCut.h"
//using namespace std;
#define M 10000
long double *result0,*result1;
long double matrix[6000][7000],temp5[70000];
 //double var,var1;
int m=0,n=0,t=0,m1,m0;
int sign;
/*
 * calculate the value of (i choose b)/(n choose b)
 */
long double c(int n, int i, int b)
 {
     long double s;
     int j=b;
     s=1.0;
     for(;b>=1;b--)
     {
         s=s*(i-b+1)/(n-b+1);
     }
     return s;
 }
/*
 * search for optimal n
 * Input: r------cost ratio, s--------- security parameter
 */
double _MajorityCut_Solver(long double r, int s)
{
    long double e0;
    long double cost=-1,cost0=-1,cost1=0;
    int i;
    m0=0;
    double c;
    if(m1<50*log(r)/log(2)) m1=50*log(r)/log(2);//choose the start point
    long double solution[700];
    do{
        input(m1,s);//set the input to the solver
        for(i=0;i<70000;i++)
            temp5[i]=0; //reset the variables
       // if (result1!=NULL) free(result1);
        result1=(long double *)malloc(sizeof (long double)*m1); // the solutions stored here.
        cost=comput();//solve LP
        long double e1;
        e1=cost;
        if (cost!=-1)
        {
        int sg;
        cost=cost*(r-1)+m1;
        cost1=cost;
        if((cost0==-1)||(cost0>cost)) //choose the cheaper solution
        {
            sign+=1;
            cost0=cost;
            m0=m1;
            e0=e1;
          //  free(result0);
            result0=result1;
            result1=NULL;
        }
        else sign=0;
        }
        m1=m1+1;
    }while(((cost0==-1)||(m1<cost0))&&((sign<10)||((cost-cost0)<10)));//search for optimal n
    m1=m0;
    printf("Excepted Cost=%LF\nn=%d \n",cost0,m1);
    for(i=0;i<m1;i++)
       if(result0[i]>0) printf("%d %Lf\n",i,result0[i]);
    return cost;
}
void MajorityCut(int s,double r)
{
    m1=s;
    _MajorityCut_Solver(r,m1);
}
