//
//  Pure.c
//  
//
//  Created by Sourgroup on 2/18/16.
//
//

#include <stdio.h>
#include <math.h>

int test (int n,int b)
{
    
    int n0=n;
    int e=2*b-1;
    int i=0;
    double node=0;
    for(i=0;i<b;i++)
    {
        
        node=node+log(n)/log(2);
        node=node-log(e)/log(2);
        n--;
        e--;
    }
    if (node>=40)return 1;
    else return 0;
}
int search(int n)
{
    int i=0;
    int b=1;
    do{
        int j=test(n,b);
        if (j==1)return b;
        else b++;
    }while (b*2-1<=n);
    return -1;
}
int cr(double r)
{
    int n=123;
    int i;
    double cost=-1;
    int n0,e0;
    do{
        i=search(n);
        double c1=n+(r-1)*(2*i-1);
        if((cost==-1)||(c1<cost)){cost=c1;n0=n;e0=2*i-1;}
        n++;
        //printf("%d %lf %d %d\n",n,cost,n0,e0);
    }while(n<cost);
    
    printf("%d %d %lf\n",n0,e0,cost);
    return 0;
}
int main()
{
    int i=3;
    for(;i<=42;i+=3)
    cr(i);
}