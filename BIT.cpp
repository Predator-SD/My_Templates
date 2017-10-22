#include<bits/stdc++.h>
#define N 1008611
#define lowbit(x) x&-x
using namespace std;
template<typename T>
struct BIT{
    struct SEMI{  
        T arr[N];  
        void add(int x,T n){while(x<=N)arr[x]+=n,x+=lowbit(x);}  
        T sum(int x){int sum=0;while(x)sum+=arr[x],x-=lowbit(x);return sum;}  
    }T1,T2;
    void add(int x,T n){T1.add(x,n);T2.add(x,x*n);}  
    void update(int L,int R,T n){add(L,n);add(R+1,-n);}  
    T sum(int x){return (x+1)*T1.sum(x)-T2.sum(x);}  
    T query(int L,int R){return sum(R)-sum(L-1);}
};
