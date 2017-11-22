#include<bits/stdc++.h>
#define maxn 1000005
using namespace std;

int a[maxn];
int root[maxn*20];

struct Chairman_Tree{
	enum Relation{
		L=0,R=1
	};
	
	int ch[maxn*20][2],val[maxn*20],index=0;
	
	inline void build(int &o,const int &l,const int &r){
		o=++index;
		
		if(l==r){
			val[o]=a[l];
			return;
		}
		
		const int mid=(l+r)>>1;
		build(ch[o][L],l,mid);
		build(ch[o][R],mid+1,r);
	}
	
	inline void modify(int &o,const int &pre,const int &l,const int &r,const int &k,const int &v){
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
}CT;

int main(){
	register int n,m;
	scanf("%d%d",&n,&m);
	
	for(register int i=1;i<=n;++i) scanf("%d",&a[i]);
	CT.build(root[0],1,n);
	
	register int pre,opt,x,y;
	for(register int i=1;i<=m;++i){
		scanf("%d%d%d",&pre,&opt,&x);
		if(opt==1){
			scanf("%d",&y);
			CT.modify(root[i],root[pre],1,n,x,y);
		}else{
			printf("%d\n",CT.query(root[pre],1,n,x));
			root[i]=root[pre];
		}
	}
	return 0;
}
