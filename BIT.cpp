#include<bits/stdc++.h>
#define MAXN 1008611
#define lowbit(x) x&-x
using namespace std;
int arr[MAXN];
inline int query(int x){int res=0;while(x)res+=arr[x],x-=lowbit(x);return res;}  
inline void add(int x,int n){while(x<MAXN)arr[x]+=n,x+=lowbit(x);}  
inline int update(int x,int y,int n){add(x,n);add(y+1,-n);}  
