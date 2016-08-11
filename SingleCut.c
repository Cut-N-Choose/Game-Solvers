#include "SingleCut.h"
long long N;
//
//Output the solution with given n.
//
void _print_result (int n)
{
    long long S=0;
    long long s=1;
    int i=n;
    int j=1;
    do{
        S=S+s;
        printf("%d %lf \n",j-1,s*1.0/N);
        s=s*i/j;
        i--;
        j++;
    }while((S+s<=N)&&(i>=1));
    printf("%d %lf \n",j-1,(N-S)*1.0/N);
    return;
}

// Input: number of circuits n;
// Output: established of circuits evaluated times 2^s
//
long long _number_of_evaluation (int n)// compute the expected number of evaluation with the setting of n circuits
{
    long long S=0;
    long long s=1;
    int i=n;
    int j=1;
    long long cost=0;
    do{
        S=S+s;
        cost=cost+s*(j-1);
        s=s*i/j;
        i--;
        j++;
    }while((S+s<=N)&&(i>=1));//Given the form of the result, here we are computing the solution of the corresponding LP problem
    cost+=(N-S)*(j-1);
    return cost;
}

// Input:
// r: cost ratio
// s: security parameter
// Search for best n
// Output: best n

int _search_for_n (double r, int s) {
    int n=s;
    long long _n_of_eval;
    double _lowest_cost=-1;
    int n0;
    do{
        _n_of_eval=_number_of_evaluation(n);
        double _expected_cost;
        _expected_cost=_n_of_eval*(1.0)/N*(r-1)+n;
        if ((_lowest_cost<0)||(_expected_cost<_lowest_cost)) {
            n0=n; _lowest_cost=_expected_cost;
        } //choose the cheaper solution
        n++;
    } while ((_lowest_cost<0)||(n<=_lowest_cost));
    printf("Cost ratio=%lf\nExpected cost=%lf\nn=%d\nSpeed up=%lf\n",r,_lowest_cost,n0,1-_lowest_cost/s*2/(1+r));
    _print_result(n0);
    return n0;
}

/*
 * Input:
 * r --- r is the cost ratio.
 *
 * Output: void
 *
 */
void SingleCut(int s, double r) {
    N=pow(2,s);
    _search_for_n (r,s);
    return;
}
