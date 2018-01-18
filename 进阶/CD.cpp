#include<cstdio>
#include<algorithm>
#include<cstring>
#define maxn 10005
#define INF 0x3f3f3f3f
using namespace std;

struct edge{
	int to,next,w;
}e[maxn<<1|1];

int n,len;
int head[maxn],k=1;

inline void addedge(int u,int v,int w){
	e[k]=(edge){v,head[u],w},head[u]=k++;
}

inline void add(int u,int v,int w){
	addedge(u,v,w);
	addedge(v,u,w);
}

int ans,sum,root,siz[maxn],f[maxn];
bool vis[maxn];
int a[maxn],t;

void getrt(int u,int fa){
	siz[u]=1,f[u]=0;
	for(register int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(vis[v]||v==fa) continue;
		getrt(v,u);
		siz[u]+=siz[v];
		f[u]=max(f[u],siz[v]);
	}
	f[u]=max(f[u],sum-siz[u]);
	if(f[u]<f[root]) root=u;
}

void dfs(int u,int w,int fa){
	a[++t]=w;
	for(register int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(vis[v]||v==fa) continue;
		dfs(v,w+e[i].w,u);
	}
}

int cal(int u,int w){
	t=0,dfs(u,w,0);
	sort(a+1,a+1+t);
	int l=1,r=t,res=0;
	while(l<r){
		if(a[l]+a[r]<=len){
			res+=r-l;
			++l;
		}else --r;
	}
	return res;
}

void solve(int u){
	vis[u]=true;
	ans+=cal(u,0);
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(vis[v]) continue;
		ans-=cal(v,e[i].w);
		root=0;
		sum=siz[v];
		getrt(v,u);
		solve(root);
	}
}

int main(){
	while(~scanf("%d%d",&n,&len),n,len){
		memset(vis,false,sizeof vis);
		memset(head,0,sizeof head);
		ans=root=0;
		k=1;
		register int u,v,w;
		for(register int i=1;i<n;++i)
			scanf("%d%d%d",&u,&v,&w),
			add(u,v,w);
		f[0]=INF;
		sum=n;
		getrt(1,0);
		solve(root);
		printf("%d\n",ans);
	}
	return 0;
}
