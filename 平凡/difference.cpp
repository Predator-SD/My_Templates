#include<bits/stdc++.h>
using namespace std;
long long f[100010],a[100010],b[100010],c[100010],n,m,p[100010];
int main(){
	register long long i=1,l,r,ans=0,re=0;
	scanf("%lld%lld",&n,&m);
	for(;i<=m;++i) scanf("%lld",&p[i]);
	for(i=1;i<=n-1;++i) scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);
	
	for(i=1;i<=m-1;++i){
		l=p[i];r=p[i+1];
		if(l>r){
			l^=r;
			r^=l;
			l^=r;
		}
		f[l]+=1;f[r]-=1;
	}
	for(i=1;i<=n-1;++i) ans+=f[i],f[i]=ans,re+=min((f[i]==0?0:c[i]+b[i]*f[i]),f[i]*a[i]);
	printf("%lld",re);
	return 0;
}
