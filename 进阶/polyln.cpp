#include<bits/stdc++.h>
#define maxn 262144
#define mod 1004535809
#define ll long long
using namespace std;

int n;
ll jie[maxn],jieinv[maxn];
ll g[maxn],ginv[maxn],gdao[maxn];
int rev[maxn];

inline ll qpow(ll a,ll b,ll m,ll ans=1){
	while(b){
		if(b&1) ans=ans*a%m;
		a=a*a%m;
		b>>=1;
	}
	return ans;
}

inline void prelude(){
	jie[0]=jieinv[0]=1;
	for(int i=1;i<=n;++i)
		jie[i]=jie[i-1]*i%mod,
		jieinv[i]=qpow(jie[i],mod-2,mod);
}

void NTT(ll *a,int n,int f){
    for(int i=0;i<n;++i)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	
    for(int h=2;h<=n;h<<=1){
        ll wn=qpow(3,(mod-1)/h,mod);
        for(int i=0;i<n;i+=h){
            ll w=1;
            for(int j=0;j<(h>>1);++j,w=w*wn%mod){
                ll t=a[i+j+(h>>1)]*w%mod;
                a[i+j+(h>>1)]=((a[i+j]-t)%mod+mod)%mod;
                a[i+j]=(a[i+j]+t)%mod;
            }
        }
    }
    
    if(f==-1){
        for(int i=1;i<(n>>1);++i) swap(a[i],a[n-i]);
        ll inv=qpow(n,mod-2,mod);
        for(int i=0;i<n;++i) a[i]=a[i]*inv%mod;
    }
}

void inverse(ll *a,ll *b,int n){
	if(n==1){b[0]=qpow(a[0],mod-2,mod);return;}
	
	static ll temp[maxn];
	inverse(a,b,n>>1);
	memcpy(temp,a,sizeof(a[0])*n);
	memset(temp+n,0,sizeof(a[0])*n);
	
	int m=n,L=0,nn=n;
    for(n=1;n<=m;n<<=1)L++;
    for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
    
    NTT(temp,n,1),
	NTT(b,n,1);
	
	for(int i=0;i<n;++i)
        temp[i]=b[i]*(((2ll-temp[i]*b[i]%mod)%mod+mod)%mod)%mod;
        
    NTT(temp,n,-1);
	for(int i=0;i<(n>>1);i++)b[i]=temp[i];
	memset(b+nn,0,sizeof(b[0])*nn);
	n=nn;
}

int main(){
	scanf("%d",&n);
	prelude();
	
	for(register int i=0;i<=n;++i)
        if(i<2)g[i]=1;
        else g[i]=qpow(2,(ll)i*(i-1)/2,mod)*jieinv[i]%mod;
    
    for(register int i=1;i<=n;++i)
        gdao[i-1]=g[i]*i%mod;
    gdao[n]=0;
    
    register int l; for(l=1;l<=n;l<<=1);
    inverse(g,ginv,l);
    
    register int m=n,L=0;
    for(n=1;n<=m;n<<=1) ++L;
    
    for(register int i=0;i<n;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
    NTT(gdao,n,1),NTT(ginv,n,1);
    for(register int i=0;i<n;++i) gdao[i]=(ginv[i]*gdao[i])%mod;
    NTT(gdao,n,-1);
    
    printf("%lld",(gdao[m-1]*qpow(m,mod-2,mod)%mod)*jie[m]%mod);
	return 0;
}
