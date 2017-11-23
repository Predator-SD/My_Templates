#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
#define N 10005
using namespace std;

int n,m;
int a[N],b[N<<1|1];

template<size_t maxn>
struct Modifiable_CT{
	enum Realtion{
		L=0,R=1
	};
	
	int sz,totx,toty,totn;
	int root[maxn];
	int xx[maxn],yy[maxn];
	int ch[maxn*600][2],size[maxn*600];
	
	void ins(int &o,const int &l,const int &r,const int &pre,const int &k,const int &v){
		o=++sz;
		
		size[o]=size[pre]+v;
		ch[o][L]=ch[pre][L],ch[o][R]=ch[pre][R];
		
		if(l==r) return ;
		const int mid=(l+r)>>1;
		if(k<=mid) ins(ch[o][L],l,mid,ch[pre][L],k,v);
		else ins(ch[o][R],mid+1,r,ch[pre][R],k,v);
	}
	
	void modify(const int &x,const int &v){
		int k=lower_bound(b+1,b+totn+1,a[x])-b;
		for(int i=x;i<=n;i+=lowbit(x)) ins(root[i],1,totn,root[i],k,v);
	}
	
	int query(int l,int r,int k){
		if(l==r) return l;
		
		int sum=0;
		const int mid=(l+r)>>1;
		
		for(int i=1;i<=totx;++i) sum-=size[ch[xx[i]][L]];
		for(int i=1;i<=toty;++i) sum+=size[ch[yy[i]][L]];
		
		if(k<=sum){
			for(int i=1;i<=totx;++i) xx[i]=ch[xx[i]][L];
			for(int i=1;i<=toty;++i) yy[i]=ch[yy[i]][L];
			return query(l,mid,k);
		}else{
			for(int i=1;i<=totx;++i) xx[i]=ch[xx[i]][R];
			for(int i=1;i<=toty;++i) yy[i]=ch[yy[i]][R];
			return query(mid+1,r,k-sum);
		}
	}
};

Modifiable_CT<N> MCT;
