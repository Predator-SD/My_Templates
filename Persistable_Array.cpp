#include<bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int base[MAXN];

template<typename T,size_t maxn>
struct Chairman_Tree{
	enum Relation{
		L=0,R=1
	};
	
	int root[maxn];
	int ch[maxn][2];
	T val[maxn];
	int index=0;
	
	inline void build(int &o,const T a[],const int &l,const int &r){
		o=++index;
		
		if(l==r){
			val[o]=a[l];
			return;
		}
		
		const int mid=(l+r)>>1;
		build(ch[o][L],a,l,mid);
		build(ch[o][R],a,mid+1,r);
	}
	
	inline void modify(int &o,const int &pre,const int &l,const int &r,const int &k,const T &v){
		o=++index;
		
		ch[o][L]=ch[pre][L],ch[o][R]=ch[pre][R],val[o]=val[pre];
		
		if(l==r){
			val[o]=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(k<=mid) modify(ch[o][L],ch[pre][L],l,mid,k,v);
		else modify(ch[o][R],ch[pre][R],mid+1,r,k,v);
	}
	
	inline int query(const int &o,const int &l,const int &r,const int &k){
		if(l==r) return val[o];
		const int mid=(l+r)>>1;
		if(k<=mid) return query(ch[o][L],l,mid,k);
		else return query(ch[o][R],mid+1,r,k);
	}
};

Chairman_Tree<int,MAXN*20> CT;

int main(){
	register int n,m;
	scanf("%d%d",&n,&m);
	
	for(register int i=1;i<=n;++i) scanf("%d",&base[i]);
	CT.build(CT.root[0],base,1,n);
	
	register int pre,opt,x,y;
	for(register int i=1;i<=m;++i){
		scanf("%d%d%d",&pre,&opt,&x);
		if(opt==1){
			scanf("%d",&y);
			CT.modify(CT.root[i],CT.root[pre],1,n,x,y);
		}else{
			printf("%d\n",CT.query(CT.root[pre],1,n,x));
			CT.root[i]=CT.root[pre];
		}
	}
	return 0;
}
