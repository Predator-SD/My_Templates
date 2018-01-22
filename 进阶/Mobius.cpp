#include<bits/stdc++.h>

#define MAXN 50005
#define ll long long

using namespace std;

int prime[MAXN],pcnt;
bool vis[MAXN];
int miu[MAXN],pfmiu[MAXN];
void prelude(){
    miu[1]=1;
    for(int i=2;i<MAXN;++i){
        if(!vis[i]){
            prime[pcnt++]=i;
            miu[i]=-1;
        }
        for(int j=0;j<pcnt&&i*prime[j]<MAXN;++j){
            int k=i*prime[j];
            vis[k]=true;
            if(i%prime[j]) miu[k]=-miu[i];
            else break;
        }
    }
    for(int i=1;i<MAXN;++i)
        pfmiu[i]=pfmiu[i-1]+miu[i];
}

int a,b,c,d,k;

ll solve(int x,int y){
    if(x>y) swap(x,y);
    ll ans=0;
    for(int i=1;i<=x;){
        int j=min(x/(x/i),y/(y/i));
        ans+=(ll)(pfmiu[j]-pfmiu[i-1])*(x/j)*(y/j);
        i=j+1;
    }
    return ans;
}

int main() {
    prelude();
    register int T;
	scanf("%d",&T);
    while(T--) {
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        ll ans=solve(b/k,d/k);
        ans-=solve((a-1)/k,d/k);
        ans-=solve(b/k,(c-1)/k);
        ans+=solve((a-1)/k,(c-1)/k);
        printf("%lld\n",ans);
    }
    return 0;
}
