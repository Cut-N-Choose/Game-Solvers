#ifndef BatchedCut_h
#define BatchedCut_h
#include <math.h>
#include "BCGFC.h"
int bbits(int N);
struct poly _compute_generation_function(int b,int n);
struct bignumber P(int b,int s,double t);
int securitycheck(int N,int B,int s, double t);
struct tb find (int N, int s, double r);
void BatchedCut(int N, int s,double r);
#endif /* BatchedCut_h */
