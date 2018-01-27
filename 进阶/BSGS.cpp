#include<cstdio>
#include<map>
#include<cmath>
#define maxn 10000000
#define ll long long
using namespace std;

inline ll qpow(ll a,ll b,ll mod,ll ans=1){while(b){if(b&1)ans=ans*a%mod;a=a*a%mod,b>>=1;}return ans;}

map<ll,int> ha;

ll BSGS(ll a,ll b,ll p){
	if(a%p==0) return -1;
	ha.clear();
	ll m=sqrt(p)+1;
	ha[b]=0; for(int j=1,ans=b;j<=m;++j) ans=ans*a%p,ha[ans]=j;
	for(ll i=1,am=qpow(a,m,p),ans=1;i<=m;++i){ans=ans*am%p; if(ha[ans]) return ((i*m-ha[ans])%p+p)%p;}
	return -1;
}

int main(){
	register ll a,b,c;
	while(~scanf("%lld%lld%lld",&c,&a,&b)){
		register ll ans=BSGS(a,b,c);
		if(ans==-1) puts("no solution");
		else printf("%lld\n",ans);
	}
	return 0;
}
