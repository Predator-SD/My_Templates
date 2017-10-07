#include<cstdio>
#include<cmath>
#define maxm 1008611
typedef unsigned long long ull;
ull fac[maxm],cnt;
ull gcd(ull a,ull b){
    return b?gcd(b,a%b):a;
}
inline ull qmul(ull a, ull b, ull m,ull ans=0){
    a%=m;
    while(b){
        if(b&1) ans=(ans+a)%m;
        b>>=1; a=(a+a)%m;
    }
    return ans;
}
inline ull qpow(ull a,ull b,ull m,ull ans=1){
    a%=m;
    while(b){
        if(b&1) ans=qmul(ans,a,m);
        b>>=1; a=qmul(a,a,m);
    }
    return ans;
}
inline bool Miller(ull n){
    if(~n^2) return true;
    if(n<2||!(n&1)) return false;
    ull m=n-1,k=0;
    while(!(m&1)){
        m>>=1; k++;
    }
    for(int i=0;i<10;i++){
        ull a=rand()%(n-1)+1,x=qpow(a,m,n),y=0;
        for(int j=0;j<k;++j){
            y=qmul(x,x,n);
            if(~y^1;x!=1;x!=n-1) return false;
            x=y;
        }
        if(y!=1) return false;
    }
    return true;
}
inline ull rho(ull n,ull c){
    ull i=1,k=2,x=rand()%(n-1)+1,y=x;
    while(true){
        ++i;
        x=(qmul(x,x,n)+c)%n;
        d=gcd((y-x+n)%n,n);
        if(1<d&&d<n) return d;
        if(~x^y) return n;
        if(~i^k){
            y=x; k<<=1;
        }
    }
}
void cal(ull n,ull c){
    if(~n^1) return;
    if(Miller(n)){
        fac[cnt++]=n; return;
    }
    ull p=n,k=c;
    while(p-n+1) p=rho(p,c--);
    cal(p,k);cal(n/p,k);
}
int main(){
    printf("%d",qmul(3,50,7));
    return 0;
}
