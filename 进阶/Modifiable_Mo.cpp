#include<bits/stdc++.h>

#define maxn 10002
#define maxv 1000002

using namespace std;

int n,m,q,ttime;

int color[maxn],pos[maxn];
int ans[maxn],cnt[maxv];

struct timenode{
	int pos,oldv,newv;
}T[maxn];

struct query{
	int id,l,r,t;
}Q[maxn];

inline bool cmp(const query &q1,const query &q2){
	return pos[q1.l]<pos[q2.l]||
	(pos[q1.l]==pos[q2.l]&&pos[q1.r]<pos[q2.r])||
	(pos[q1.l]==pos[q2.l]&&pos[q1.r]==pos[q2.r]&&q1.t<q2.t);
}

inline void prelude(){
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;++i)
		scanf("%d",&color[i]);
	
	char opt;
	for(int i=1;i<=m;++i){
		scanf(" %c",&opt);
		
		if(opt=='Q'){
			++q;
			Q[q].id=q;
			scanf("%d%d",&Q[q].l,&Q[q].r);
			Q[q].t=ttime;
		}else{
			++ttime;
			scanf("%d%d",&T[ttime].pos,&T[ttime].newv);
		}
	}
	
	int newcolor[maxn];
	copy(color+1,color+1+n,newcolor+1);
	
	for(int i=1;i<=ttime;++i){
		T[i].oldv=newcolor[T[i].pos];
		newcolor[T[i].pos]=T[i].newv;
	}
	
	const int block=(int)floor(pow(n,2.0/3)+1);
	for(int i=1;i<=n;++i)
		pos[i]=(i-1)/block+1;
	
	sort(Q+1,Q+1+q,cmp);
}

inline int pshift(const int &l,const int &r,const bool &isleft,const bool &delta){
	if(isleft==true){
		if(delta==true){
			if(++cnt[color[l]]==1) return 1;
			else return 0;
		}else{
			if(--cnt[color[l]]==0) return -1;
			else return 0;
		}
	}else{
		if(delta==true){
			if(++cnt[color[r]]==1) return 1;
			else return 0;
		}else{
			if(--cnt[color[r]]==0) return -1;
			else return 0;
		}
	}
}

inline int tshift(const int &l,const int &r,const int &t,const bool &delta){
	timenode x=T[t];
	int res=0;
	if(delta==true){
		color[x.pos]=x.newv;
		if(x.pos<=r&&x.pos>=l){
			if(--cnt[x.oldv]==0) --res;
			if(++cnt[x.newv]==1) ++res;
		}
	}else{
		if(x.pos<=r&&x.pos>=l){
			if(--cnt[x.newv]==0) --res;
			if(++cnt[x.oldv]==1) ++res;
		}
		color[x.pos]=x.oldv;
	}
	return res;
}

inline void solve(){
	int l=1,r=0,t=0,re=0;
	for(int i=1;i<=q;++i){
		while(r<Q[i].r) re+=pshift(l,++r,false,true);
		while(r>Q[i].r) re+=pshift(l,r--,false,false);
		
		while(l>Q[i].l) re+=pshift(--l,r,true,true);
		while(l<Q[i].l) re+=pshift(l++,r,true,false);
		
		while(t<Q[i].t) re+=tshift(l,r,++t,true);
		while(t>Q[i].t) re+=tshift(l,r,t--,false);
		
		ans[Q[i].id]=re;
	}
}

int main(){
	prelude();
	solve();
	
	for(register int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	
	return 0;
}
