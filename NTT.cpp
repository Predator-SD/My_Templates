#include<bits/stdc++.h>
#define ll long long
#define MAXN 1<<20
using namespace std;

const int p=479<<21|1;
ll inv,gn[MAXN],gn_inv[MAXN];

int n;

inline ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%p;
		a=a*a%p;
		
		b>>=1;
	}
	
	return ans;
}

inline void rev(const int &n,ll r[]){
	for(int i=0,j=0;i<n;++i){
        if(i>j)
			swap(r[i],r[j]);
			
        for(int l=n>>1;(j^=l)<l;l>>=1);
    }
}

inline void prelude(){
	inv=qpow(3,p-2);
	
	for(int i=1;i<=n;i<<=1)
		gn[i]=qpow(3,(p-1)/i),
		gn_inv[i]=qpow(inv,(p-1)/i);
}

inline void NTT(int n,ll* r,short f){
    rev(n,r);
    
    for(int i=2;i<=n;i<<=1){
        int m=i>>1;
        
        for(int j=0;j<n;j+=i){
            ll w=1,wn=(f==1?gn[i]:gn_inv[i]);
            
            for(int k=0;k<m;++k){
                ll z=r[j+m+k]*w%p;
                
                r[j+m+k]=(r[j+k]-z+p)%p;
                r[j+k]=(r[j+k]+z)%p;
                
                w=w*wn%p;
            }
        }
    }
    
    if(f==-1){
        ll n_inv=qpow(n,p-2);
        for(int i=0;i<n;++i) r[i]=r[i]*n_inv%p;
    }
}
