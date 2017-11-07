#include<bits/stdc++.h>
#define maxn 1008611
#define inf 0x7fffffff
#define maxx(a,b) (a)>(b)?(a):(b)
#define minn(a,b) (a)<(b)?(a):(b)
#define ll long long
using namespace std;

template<typename T>
inline void read(T &x){
	x=0;char ch=getchar();short f=1;while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar(); x*=f;
}

int _sum,_max,_min;

struct seg{
	int sumv,minv,maxv,L,R,addv,setv;
}tr[maxn<<2|1];

void build(int o,int a[],int l,int r){
	tr[o].L=l,tr[o].R=r,tr[o].addv=0,tr[o].setv=-inf;
	if(l==r){
	    tr[o].sumv=a[l];
	    tr[o].maxv=a[l],tr[o].minv=a[l];
	}else{
	    int mid=l+((r-l)>>1);
	    build(o<<1,a,l,mid),build(o<<1|1,a,mid+1,r);
	    tr[o].sumv=tr[o<<1].sumv+tr[o<<1|1].sumv;
	    tr[o].maxv=maxx(tr[o<<1].maxv,tr[o<<1|1].maxv);
	    tr[o].minv=minn(tr[o<<1].minv,tr[o<<1|1].minv);
	}
}

void maintain(int o){
	tr[o].sumv=tr[o].maxv=tr[o].minv=0;
	if(tr[o].R>tr[o].L){
		tr[o].sumv=tr[o<<1].sumv+tr[o<<1|1].sumv;
		tr[o].minv=minn(tr[o<<1].minv,tr[o<<1|1].minv);
		tr[o].maxv=maxx(tr[o<<1].maxv,tr[o<<1|1].maxv);
	}
	if(tr[o].addv) tr[o].maxv+=tr[o].addv,tr[o].minv+=tr[o].addv,tr[o].sumv+=tr[o].addv*(tr[o].R-tr[o].L+1);
}

void pushdown(int o){
	if(tr[o].setv!=-inf)
		tr[o<<1].setv=tr[o<<1|1].setv=tr[o].setv,tr[o].setv=-inf;
}

void sss(int o,int ql,int qr,int v){
	if(ql<=tr[o].L&&qr>=tr[o].R) tr[o].setv=v;
	else{
		pushdown(o);
		int mid=tr[o].L+((tr[o].R-tr[o].L)>>1);
	    if(ql<=mid) sss(o<<1,ql,qr,v); else maintain(o<<1);
		if(qr>mid) sss(o<<1|1,ql,qr,v); else maintain(o<<1|1);
	}
	maintain(o);
}

void qqq2(int o,int ql,int qr){
	if(tr[o].setv!=-inf){
		_sum+=tr[o].setv*(minn(qr,tr[o].R)-maxx(ql,tr[o].L)+1);
		_min=minn(_min,tr[o].setv);
		_max=maxx(_max,tr[o].setv);
	}else if(ql<=tr[o].L&&qr>=tr[o].R){
		_sum+=tr[o].sumv;
		_min=minn(_min,tr[o].minv);
		_max=maxx(_max,tr[o].maxv);
	}else{
		int mid=tr[o].L+((tr[o].R-tr[o].L)>>1);
		if(ql<=mid) qqq2(o<<1,ql,qr);
		if(qr>mid) qqq2(o<<1|1,ql,qr);
	}
}

void uuu(int o,int ql,int qr,int v){
	if(ql<=tr[o].L&&qr>=tr[o].R) tr[o].addv+=v;
	else{
		int mid=tr[o].L+((tr[o].R-tr[o].L)>>1);
	    if(ql<=mid) uuu(o<<1,ql,qr,v);
		if(qr>mid) uuu(o<<1|1,ql,qr,v);
	}
	maintain(o);
}

void qqq(int o,int ql,int qr,int add){
	if(ql<=tr[o].L&&qr>=tr[o].R)
		_sum+=tr[o].sumv+add*(tr[o].R-tr[o].L+1),_max=maxx(_max,tr[o].maxv+add),_min=minn(_min,tr[o].minv+add);
	else{
		int mid=tr[o].L+((tr[o].R-tr[o].L)>>1);
		if(ql<=mid) qqq(o<<1,ql,qr,add+tr[o].addv);
		if(qr>mid) qqq(o<<1|1,ql,qr,add+tr[o].addv);
	}
}

void init(int a[],int n){
	build(1,a,1,n);
}

void set(int l,int r,int v){
	sss(1,l,r,v);
}

void update(int l,int r,int v){
	uuu(1,l,r,v);
}

void query(int l,int r){
	_sum=0,_max=-inf,_min=inf;
	qqq(1,l,r,0);
	//qqq2(1,l,r);
}
