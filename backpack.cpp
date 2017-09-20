#include<cstdio>
#include<algorithm>
using namespace std;
int c[110],w[110],m[110],dp[100010],V;

void ZeroOne(int cost,int weight){
    for(int i = V; i >= cost; i--)
        dp[i] = max(dp[i],dp[i-cost]+weight);
}

void Complete(int cost,int weight){
    for(int i = cost; i <= V; i++)
        dp[i] = max(dp[i],dp[i-cost]+weight);
}

void Multiple(int cost,int weight,int n){
    if(V <= n*cost){
        Complete(cost,weight);
        return;
    }
    else{
        int k = 1;
        while(k <= n){
            ZeroOne(k*cost,k*weight);
            n -= k;
            k <<= 1;
        }
        ZeroOne(n*cost,n*weight);
    }
}
