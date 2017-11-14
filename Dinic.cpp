#include<bits/stdc++.h>
#define minn(a,b) (a)<(b)?(a):(b)
#define INF 0x3f3f3f3f
#define maxn 1008611
using namespace std;

namespace Dinic{
	struct edge{
		int from,to,cap,flow;
	};

	int n,m,s,t;
	vector<edge> edges; vector<int> G[maxn];
	bool vis[maxn];
	int d[maxn],cur[maxn];
	
	inline bool BFS(){
		memset(vis,false,sizeof vis);
		queue<int> Q; Q.push(s),d[s]=0,vis[s]=true;
		while(Q.empty()==false){
			int x=Q.front(); Q.pop();
			for(int i=0;i<G[x].size();++i){
				edge& e=edges[G[x][i]];
				if(!vis[e.to]&&e.cap>e.flow){
					vis[e.to]=true;
					d[e.to]=d[x]+1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}
	
	int DFS(int x,int a){
		if(x==t||a==0) return a;
		int flow=0,f;
		for(int& i=cur[x];i<G[x].size();++i){
			edge& e=edges[G[x][i]];
			if(d[e.to]==d[x]+1&&(f=DFS(e.to,minn(a,e.cap-e.flow)))>0){
				e.flow+=f,edges[G[x][i]^1].flow-=f;
				flow+=f,a-=f;
				if(a==0) break;
			}
		}
		return flow;
	}
	
	int solve(){
		int flow=0;
		while(BFS())
		    memset(cur,0,sizeof cur),flow+=DFS(s,INF);
		return flow;
	}
}
