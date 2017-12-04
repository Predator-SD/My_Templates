#include<cstdio>
#include<cstring>
using namespace std;
int c[10086],topo[10086],t,G[10086][10086];
bool dfs(int u){
	c[u]=-1;
	for(int v=0;v<t;v++){
		if(G[u][v]) if(c[v]==-1) return false;
		else if(!c[u]&&!dfs(v)) return false;
	}
	c[u]=1; topo[--t]=u;
	return true;
}
bool toposort(){
	memset(c,0,sizeof(c));
	for(int u=0;u<t;u++) if(!c[u]&&!dfs(u)) return false;
	return true;
}
