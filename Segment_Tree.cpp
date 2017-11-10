#include<bits/stdc++.h>
#define inf 0x7fffffff
#define maxn 1008611
#define maxx(a,b) (a)>(b)?(a):(b)
#define minn(a,b) (a)<(b)?(a):(b)
#define lc o<<1
#define rc o<<1|1
using namespace std;

int n=100;
int _sum,_max;
int sumv[maxn],addv[maxn],maxv[maxn];
int ql,qr;

void maintain(int o,int l,int r){
    sumv[o]=maxv[o]=0;
    if(r>l){
        sumv[o]=sumv[lc]+sumv[rc];
        maxv[o]=maxx(maxv[lc],maxv[rc]);
    }
    if(addv[o]) sumv[o]+=(r-l+1)*addv[o],maxv[o]+=addv[o];
}

void uuu(int o,int l,int r,int x){
    if(ql<=l&&qr>=r) addv[o]+=x;
    else{
        int mid=(l+r)>>1;
        if(ql<=mid) uuu(lc,l,mid,x);
        if(qr>mid) uuu(rc,mid+1,r,x);
    }
    maintain(o,l,r);
}

void qqq(int o,int l,int r,int add){
    if(ql<=l&&qr>=r) _sum+=sumv[o]+add*(r-l+1),_max=maxx(_max,maxv[o]+add);
    else{
        int mid=(l+r)>>1;
        if(ql<=mid) qqq(lc,l,mid,add+addv[o]);
        if(qr>mid) qqq(rc,mid+1,r,add+addv[o]);
    }
}

void update(int l,int r,int v){
    ql=l,qr=r;
    uuu(1,1,n,v);
}

void query(int l,int r){
    ql=l,qr=r,_sum=0,_max=-inf;
    qqq(1,1,n,0);
}

int main(){
    memset(maxv,0,sizeof maxv);
    memset(addv,0,sizeof addv);
    memset(sumv,0,sizeof sumv);
    for(register int i=1;i<=n;++i){
        update(i,i,i);
    }
    update(2,5,7);
    query(1,10);
    printf("%d,%d",_max,_sum);
    return 0;
}
