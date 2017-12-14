#include<cstdio>
#include<cstring>

#define MAXN 500
#define INF 0x3f3f3f
#define minn(a,b) ((a)<(b)?(a):(b))

int n,a[MAXN];
int s[MAXN],f[MAXN][MAXN],p[MAXN][MAXN];

inline void prelude(){
	scanf("%d",&n);
	
	for(int i(1);i<=n;++i)
		scanf("%d",&a[i]);
	
	memset(f,INF,sizeof f);
	
	for(int i(1);i<=n;++i)
		s[i]=a[i]+s[i-1];
		
	for(int i(1);i<=n;++i)
		f[i][i]=0,
		p[i][i]=p[i][i+1]=i,
		f[i][i+1]=s[i+1]-s[i-1];
}

inline void cal(){
	for(int l(1);l<n;++l)
		for(int i(1);i+l<=n;++i){
			int j=i+l;
			
			for(int k(p[i][j-1]);k<=p[i+1][j];++k)
				if(f[i][k]+f[k+1][j]+s[j]-s[i-1]<f[i][j])
					f[i][j]=f[i][k]+f[k+1][j]+s[j]-s[i-1],
					p[i][j]=k;
		}
}

inline void solve(){
	printf("%d",f[1][n]);
}

int main(){
	prelude();
	cal();
	solve();
	return 0;
}
