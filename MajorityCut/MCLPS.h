//
//  MCLPS.h
//  
//
//  Created by Sourgroup on 6/30/16.
//
//

#ifndef MCLPS_h
#define MCLPS_h

#include <stdio.h>
#include <math.h>   
#define M 10000
extern long double *result0,*result1;
extern long double matrix[6000][7000],temp5[70000];
//double var,var1;
extern int m,n,t,m1,m0;
extern long double c(int n, int i, int b);
void input(int m1,int s);
long double comput();
#endif /* MCLPS_h */
