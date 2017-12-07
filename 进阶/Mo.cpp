#include<cstdio>
#include<algorithm>

#define ll long long

#define maxn 50005

int n,m;
ll ans;

int color[maxn],pos[maxn];
ll sum[maxn];

struct query{
	int id,l,r;
	ll up,down;
}Q[maxn];

inline bool cmp1(const query &q1,const query &q2){
	return pos[q1.l]<pos[q2.l]||(pos[q1.l]==pos[q2.l]&&q1.r<q2.r);
}

inline bool cmp2(const query &q1,const query &q2){
	return q1.id<q2.id;
}

ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}

inline void update(const int &p,const bool &delta){
	ans=ans+((sum[color[p]]<<1)+(delta?1:-1))*(delta?1:-1);
	sum[color[p]]+=delta?1:-1;
}

inline void prelude(){
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;++i)
		scanf("%d",&color[i]);
	
	pos[0]=sqrt(n);
	for(int i=1;i<=m;++i){
		Q[i].id=i;
		scanf("%d%d",&Q[i].l,&Q[i].r);
		Q[i].down=(ll)(Q[i].r-Q[i].l+1)*(Q[i].r-Q[i].l);
	}
	
	std::sort(Q+1,Q+1+m,cmp1);
}

inline void solve(){
	ll g;
	for(int i=1,l=1,r=0;i<=m;++i){
		for(;r<Q[i].r;++r)
			update(r+1,true);
		for(;r>Q[i].r;--r)
			update(r,false);
		
		for(;l<Q[i].l;++l)
			update(l,false);
		for(;l>Q[i].l;--l)
			update(l-1,true);
			
		if(Q[i].l==Q[i].r){
			Q[i].up=0;
			Q[i].down=1;
			continue;
		}
		
		Q[i].up=ans-(Q[i].r-Q[i].l+1);
		
		g=gcd(Q[i].up,Q[i].down);
		Q[i].up/=g;
		Q[i].down/=g;
	}
	
	std::sort(Q+1,Q+1+m,cmp2);
}

int main(){
	prelude();
	solve();
	
	for(register int i=1;i<=m;++i)
		printf("%lld/%lld\n",Q[i].up,Q[i].down);
		
	return 0;
}
