//
//  MCLPS.c
//  
//
//  Created by Sourgroup on 6/30/16.
//
//

#include "MCLPS.h"

/*
 * Set the input to the LP solver, which corresponds the case where security parametr is s and number of circuits is m1
 Input: m1---- number of circuits
        s----- security paramerer
 */
void input(int m1,int s)
{
    int i,j;
    m=m1;
    n=m1+1;
    //printf("m=:%d ",m);
    for (i=0;i<=n+1;i++)
        for (j=0;j<=m+n+n;j++)
            matrix [i][j]=0;
    for (i=1;i<n;i++)
    {
        for (j=i;(j<=m)&&(j<=2*i);j++)
        {
            matrix [i][j]=c(m,j,i);
        }
        matrix[i][m+1]=1;
        matrix[i][m+2]=pow(0.5,s);
    }
    for (j=1;j<=m;j++)
        matrix[n][j]=1;
    matrix[n][m+1]=-1;
    matrix[n][m+2]=1-pow(0.5,s);
    for (i=1;i<=m;i++)
        matrix [0][i]=i;
    t=1;
    for (i=1;i<=n;i++)
    {
        matrix [i][0]=matrix [i][m+2];
        matrix [i][m+2]=0;
    }
    if(t==-1)
        for(i=1;i<=m;i++)
            matrix [0][i]=(-1)*matrix [0][i];
    for(i=1;i<=n;i++)
    {
        matrix [i][m+i]=matrix [i][m+1];
        if(i!=1)
            matrix [i][m+1]=0;
    }
}

/* LP solver
 * Solver the LP problem which is set by "input"
 * return -1 if there is no solution
 * otherwise return the target value
 * the corresponding solution is stored in temp5
 */
long double comput()
{
    int i,j,flag,temp1,temp2,h,k=0,temp3[70000];
    long double a,b[70000],temp,temp4[70000],f=0,aa,d,c;
    for(i=1;i<=n;i++)
        temp3[i]=0;
    for(i=0;i<11;i++)
    {    temp4[i]=0;
        temp5[i]=0;
    }
    for(i=1;i<=n;i++)
    {
        if(matrix [i][m+i]==-1)
        {
            matrix [i][m+n+i]=1;
            matrix [0][m+n+i]=M;
            temp3[i]=m+n+i;
        }
        else
            temp3[i]=m+i;
    }
    for(i=1;i<=n;i++)
        temp4[i]=matrix [0][temp3[i]];
    do{
        for(i=1;i<=m+n+n;i++)
        {
            a=0;
            for(j=1;j<=n;j++)
                a+=matrix [j][i]*temp4[j];
            matrix [n+1][i]=matrix [0][i]-a;
        }
        for(i=1;i<=m+n+n;i++)
        {
            if(matrix [n+1][i]>=0) flag=1;
            else
            {
                flag=-1;
                break;
            }
        }
        if(flag==1)
        {     for(i=1;i<=n;i++)
        {
            if(temp3[i]<=m+n) temp1=1;
            else
            {
                temp1=-1;
                break;
            }
        }
            if(temp1==1)
            {
                for(i=1;i<=n;i++)
                    temp5[temp3[i]]=matrix [i][0];
                f=0;
               // var1=0;
                for(i=1;i<=m;i++)
                {
                    f+=i*temp5[i];// here is the result;
                    result1[i]=temp5[i];
                 //   var1+=i*i*temp5[i];
                }
               // var1=var1-f*f;
                return f;
            }
            else
            {
                return -1;
            }
        }
        if(flag==-1)
        {
            temp=100000;
            for(i=1;i<=m+n+n;i++)
                if(matrix [n+1][i]<temp)
                {
                    temp=matrix [n+1][i];
                    h=i;
                }
            for(i=1;i<=n;i++)
            {
                if(matrix [i][h]<=0) temp2=1;
                else {
                    temp2=-1;
                    break;
                }
            }
        }
        if(temp2==1)
        {
            return -1;
        }
        if(temp2==-1)
        {
            c=100000;
            for(i=1;i<=n;i++)
            {
                if(matrix [i][h]!=0)  b[i]=matrix [i][0]/matrix[i][h];
                if(matrix [i][h]==0)  b[i]=100000;
                if(b[i]<0)     b[i]=100000;
                if(b[i]<c)
                {
                    c=b[i];
                    k=i;
                }
            }
            temp3[k]=h;
            temp4[k]=matrix[0][h];
            d=matrix [k][h];
            for(i=0;i<=m+n+n;i++)
                matrix [k][i]=matrix [k][i]/d;
            for(i=1;i<=n;i++)
            { if(i==k)
                continue;
                aa=matrix [i][h];
                for(j=0;j<=m+n+n;j++)
                    matrix [i][j]=matrix [i][j]-aa*matrix [k][j];
            }
        }
    }
    while(1);
    return -1;
}