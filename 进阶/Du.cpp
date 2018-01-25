#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxx=20000000;

int mu[20000005],prime[1300010],cnt;
bool vis[20000005];

map<ll,ll> v;

inline void prelude(){
	mu[1]=1;
	for(int i=2;i<=maxx;++i){
		if(!vis[i])
			prime[++cnt]=i,
			mu[i]=-1;
		for(int j=1;j<=cnt&&i*prime[j]<=maxx;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0) break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=2;i<=maxx;++i) mu[i]+=mu[i-1];
}

ll Du_Sieve(ll n){
	if(n<=maxx) return mu[n];
	if(v[n]) return v[n];
	ll ans=1;
	for(ll i=2,j;i<=n;i=j+1){
		j=n/(n/i);
		ans-=Du_Sieve(n/i)*(j-i+1);
	}
	return v[n]=ans;
}

int main(){
	prelude();
	register ll a,b;
	scanf("%lld%lld",&a,&b);
	printf("%lld",Du_Sieve(b)-Du_Sieve(a-1));
	return 0;
}
