#include<bits/stdc++.h>
#define abss(a) ((a)<0?(-(a)):(a))
using namespace std;

int n;
const double EPS=1e-6;
double **A=new double*[22];
double *f=new double[22];

inline void prelude(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%lf",f+i);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j){
            double q;
            scanf("%lf",&q);
            A[i][j]=2*(q-f[j]);
            A[i][n+1]+=q*q-f[j]*f[j];
        }
}

inline void gauss(){
    int to;
    double t;
    for(int i=1;i<=n;++i){
        for(to=i;to<=n;++to)
            if(fabs(A[to][i])>EPS)
                break;
        if(to>n) continue;
        if(to!=i)
            for(int j=1;j<=n+1;++j)
                swap(A[to][j],A[i][j]);
        
        t=A[i][i];
        for(int j=i;j<=n+1;++j) A[i][j]/=t;
        for(int j=1;j<=n;++j)
            if(j!=i){
                t=A[j][i];
                for(int k=1;k<=n+1;++k) A[j][k]-=t*A[i][k];
            }
    }
}

int main(){
    for(register int i=0;i<22;++i) A[i]=new double[22];
    prelude();
    gauss();
    for(register int i=1;i<n;++i) printf("%.3lf ",A[i][n+1]);
    printf("%.3lf",A[n][n+1]);
    for(register int i=0;i<22;++i)
        delete[] A[i];
    delete[] A;
    delete[] f;
    return 0;
}
