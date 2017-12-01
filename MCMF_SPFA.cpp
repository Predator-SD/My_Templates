#include<cstdio>
#include<queue>

#define INF 0x3f3f3f3f
#define MAXN 5005
#define MAXM 50005

#define minn(a,b) ((a)<(b)?(a):(b))

int n,m;

struct MCMF{
	int s,t;
	
	int flow,cost;
	int cnt,head[MAXN],next[MAXM<<1|1];
	int dis[MAXN],res[MAXN],pre[MAXN];
	
	bool inq[MAXN];
	
	std::queue<int> Q;
	
	struct Edge{
		int u,v,c,f,cost;
		
		Edge(){}
		Edge(int u,int v,int c,int f,int cost):u(u),v(v),c(c),f(f),cost(cost){}
	}e[MAXM<<1|1];
	
	MCMF(){
		for(int i=0;i<=MAXN;++i) head[i]=-1;
	}
	~MCMF(){
		printf("%d %d\n",flow,cost);
	}
	
	inline void addedge(int u,int v,int c,int cost){
		e[cnt]=Edge(u,v,c,0,cost);
		next[cnt]=head[u];
		head[u]=cnt++;
		
		e[cnt]=Edge(v,u,0,0,-cost);
		next[cnt]=head[v];
		head[v]=cnt++;
	}
	
	inline bool SPFA(){
		for(int i=0;i<=n;++i) dis[i]=INF,inq[i]=false;
		dis[s]=0,inq[s]=true,res[s]=INF,Q.push(s);
		
		while(Q.empty()==false){
			int u=Q.front();
			Q.pop(),inq[u]=false;
			
			for(int i=head[u];i!=-1;i=next[i]){
				Edge &ed=e[i];
				
				if(ed.c>ed.f&&dis[ed.v]>dis[u]+ed.cost){
					dis[ed.v]=dis[u]+ed.cost;
					res[ed.v]=minn(ed.c-ed.f,res[u]);
					pre[ed.v]=i;
					
					if(!inq[ed.v])
						Q.push(ed.v),inq[ed.v]=true;
				}
			}
		}
		
		if(dis[t]==INF) return false;
		
		flow+=res[t];
		cost+=res[t]*dis[t];
		
		for(int u=t;u!=s;u=e[pre[u]].u){
			e[pre[u]].f+=res[t];
			e[pre[u]^1].f-=res[t];
		}
		
		return true;
	}
	
	inline void solve(){
		while(SPFA());
	}
};

MCMF a;

int main(){
	scanf("%d%d%d%d",&n,&m,&a.s,&a.t);
	
	register int u,v,c,cost;
	for(int i=1;i<=m;++i){
		scanf("%d%d%d%d",&u,&v,&c,&cost);
		a.addedge(u,v,c,cost);
	}
	
	a.solve();
	
	return 0;
}
