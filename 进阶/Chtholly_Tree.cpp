#include<cstdio>
#include<algorithm>

#define ll long long

#define INF 0x7fffffff
#define MAXN 100005
#define MOD 1000000007

#define minn(a,b) ((a)<(b)?(a):(b))
#define maxx(a,b) ((a)>(b)?(a):(b))
#define swapp(a,b) a^=b,b^=a,a^=b
#define inter(l1,r1,l2,r2) maxx(minn(r1,r2)-maxx(l1,l2)+1,0)



int _w;

int n,m,seed,vmax;
ll a[MAXN];

inline int rnd(){
	int ret(seed);
	seed=int((1LL*seed*7+13)%MOD);
	return ret;
}



namespace Chtholly_Tree{
	class iter{
	public:
		ll first;
		int second;
		
		iter(){}
		iter(const ll &fir,const int &sec):first(fir),second(sec){}
	};
	
	inline bool cmp(const iter &lhs,const iter &rhs){
		return lhs.first<rhs.first;
	}
	
	iter CT[MAXN],temp[MAXN];
	int sz,tsz;
	
	inline void prelude(){
		sz=1,
		CT[0]=iter(a[1],0);
	
		for(int i(1);i<=n;++i)
			if(CT[sz-1].first==a[i])
				++CT[sz-1].second;
			else
				CT[sz]=(iter){a[i],1},
				++sz;
	}
	
	inline void append(const ll &x,const int &cnt){
		if(tsz&&temp[tsz-1].first==x)
			temp[tsz-1].second+=cnt;
		else
			temp[tsz]=(iter){x,cnt},
			++tsz;
	}
	
	inline void add(const int &l,const int &r,const int &x){
		int L(0),R(0);
		tsz=0;
	
		for(int i(0);i<sz;++i){
			L=R+1,
			R=L+CT[i].second-1;
		
			ll num=CT[i].first;
		
			int cntl(inter(L,l-1,L,R)),
			cntm(inter(l,r,L,R)),
			cntr(inter(r+1,R,L,R));
		
			if(cntl) append(num,cntl);
			if(cntm) append(num+x,cntm);
			if(cntr) append(num,cntr);
		}
	
		sz=tsz;
		for(int i(0);i<sz;++i)
			CT[i]=temp[i];
	}
	
	inline void modify(const int &l,const int &r,const int &x){
		int L(0),R(0);
		tsz=0;
	
		for(int i(0);i<sz;++i){
			L=R+1,
			R=L+CT[i].second-1;
		
			ll num(CT[i].first);
		
			int cntl(inter(L,l-1,L,R)),
			cntm(inter(l,r,L,R)),
			cntr(inter(r+1,R,L,R));
		
			if(cntl) append(num,cntl);
			if(cntm) append(x,cntm);
			if(cntr) append(num,cntr);
		}
	
		sz=tsz;
		for(int i(0);i<sz;++i)
			CT[i]=temp[i];
	}
	
	ll kth(const int &l,const int &r,const int &k){
		int L(0),R(0);
		tsz=0;
		
		for(int i=0;i<sz;++i){
			L=R+1,
			R=L+CT[i].second-1;
			
			int cnt(inter(l,r,L,R));
			if(cnt) temp[tsz++]=iter(CT[i].first,cnt);
		}
		
		std::sort(temp,temp+tsz,cmp);
		L=R=0;
		
		for(int i(0);i<tsz;++i){
			L=R+1,
			R=L+temp[i].second-1;
			
			if(k>=L&&k<=R)
				return temp[i].first;
		}
		
		return -INF;
	}
}

using namespace Chtholly_Tree;



inline int qpow(int a,int b,const int &mod,int ans=1){
	while(b){
		if(b&1) ans=int(1LL*ans*a%mod);
		
		a=int(1LL*a*a%mod),
		b>>=1;
	}
	
	return ans;
}

inline int cal(const int &l,const int &r,const int &x,const int &y,int ans=0){
	int L(0),R(0);
	
	for(int i(0);i<sz;++i){
		L=R+1,
		R=L+CT[i].second-1;
		
		int cnt(inter(l,r,L,R));
		if(cnt) ans=int((ans+1LL*cnt*qpow(int(CT[i].first%y),x,y))%y);
	}
	
	return ans;
}



int main(){
	_w=scanf("%d%d%d%d",&n,&m,&seed,&vmax);
	
	for(register int i(1);i<=n;++i)
		a[i]=rnd()%vmax+1;
	
	prelude();
	
	for(register int i(1);i<=m;++i){
		int op,l,r,x,y;
		
		op=rnd()%4+1,
		l=rnd()%n+1,
		r=rnd()%n+1;
		
		if(l>r) swapp(l,r);
		
		if(op==3)
			x=rnd()%(r-l+1)+1;
		else
			x=rnd()%vmax+1;
		
		if(op==4)
			y=rnd()%vmax+1;
		
		if(op==1) add(l,r,x);
		else if(op==2) modify(l,r,x);
		else if(op==3) printf("%lld\n",kth(l,r,x));
		else if(op==4) printf("%d\n",cal(l,r,x,y));
	}
	
	return 0;
}
