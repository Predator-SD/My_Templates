#include<cstdio>
#include<cstdlib>
using namespace std;
typedef unsigned long long ull;
inline ull qmul(ull a, ull b, ull m){
    ull ans=0;a%=m;
    while(b){
        if(b&1) ans=(ans+a)%m;
        b>>=1; a=(a+a)%m;
    }
    return ans;
}
inline ull qpow(ull a,ull b,ull m){
    ull ans=1;a%=m;
    while(b){
        if(b&1) ans=qmul(ans,a,m);
        b>>=1; a=qmul(a,a,m);
    }
    return ans;
}
inline cm(ull n,ull m,ull p){
	if(n<m) return 0;
	if(m>n-m) m-n-m;
	ull s1=1,s2=1;
	for(ull i=0;i<m;i++){
		s1=qmul(s1,n-i,p); s2=qmul(s2,i+1,p);
	}
	return qmul(s1,qpow(s2,p-2,p),p);
}
ull lucas(ull n,ull m,ull p){
	if(m==0) return 1;
	return qmul(cm(n%p,n%p,p),lucas(n/p,m/p,p),p);
}
