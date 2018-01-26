#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#define lb long double
using namespace std;

const double INF=1e100;
const int MAXN=100;
const double EPS=1e-8;

int n,m,t;
lb a[MAXN][MAXN];
int base[MAXN],nonbase[MAXN];

inline int dcmp(double x){
	return fabs(x)<EPS?0:(x<0?-1:1);
}

inline void getpara(){
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;++i)
		scanf("%Lf",&a[0][i]);
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j)
			scanf("%Lf",&a[i][j]),
			a[i][j]=-a[i][j];
		scanf("%Lf",&a[i][0]);
	}
}

inline void pivot(int from,int to){
	swap(base[from],nonbase[to]);
	lb k=a[from][to];
	a[from][to]=-1.0;
	for(int i=0;i<=n;++i) a[from][i]/=-k;
	for(int i=0;i<=m;++i){
		if(i==from||dcmp(a[i][to])==0) continue;
		k=a[i][to];
		a[i][to]=0;
		for(int j=0;j<=n;++j)
			a[i][j]+=k*a[from][j];
	}
}

inline bool prelude(){
	for(int i=1;i<=n;++i) nonbase[i]=i;
	for(int i=1;i<=m;++i) base[i]=i+n;
	
	for(int x=0,y=0;;x=y=0){
		for(int i=1;i<=m;++i)
			if(dcmp(a[i][0])<0&&((rand()&1)||!x))
				x=i;
		if(!x) return true;
		for(int i=1;i<=n;++i)
			if(dcmp(a[x][i])>0&&((rand()&1)||!y))
				y=i;
		if(!y) return false;
		pivot(x,y);
	}
}

inline int simplex(){
	if(!prelude()) return 0;
	for(int from=0,to=0;;from=to=0){
		for(int i=1;i<=n;++i)
			if(dcmp(a[0][i])>0){
				to=i;
				break;
			}
		if(!to) return 1;
		lb minv=INF;
		for(int i=1;i<=m;++i){
			double k=-a[i][0]/a[i][to];
			if(dcmp(a[i][to])<0&&dcmp(k-minv)<0)
				from=i,minv=k;
		}
		if(!from) return -1;
		pivot(from,to);
	}
}

int main(){
	srand(998244353);
	getpara();
	switch(simplex()){
	case 1:
		printf("%.10Lf\n",a[0][0]);
		if(t){
			static int table[MAXN];
			for(int i=1;i<=m;++i) table[base[i]]=i;
			for(int i=1;i<=n;++i)
				if(!table[i]) printf("0 ");
				else printf("%.10Lf ",a[table[i]][0]);
			puts("");
		}
		break;
	case 0:
		puts("Infeasible");
		break;
	case -1:
		puts("Unbounded");
		break;
	default:
		break;
	}
	return 0;
}
