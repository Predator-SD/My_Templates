#include<cstdio>
using namespace std;
struct edge{
	int fr,to;
	edge(int u,int v):fr(u),to(v){}
};
edge euler(int u){
	int i=0;
	edge e[10086];
	for(int v=0;v<n;v++){
		if(G[u][v]&&!vis[u][v]){
			vis[u][v]=vis[v][u]=1;
			euler(v);
			e[i++]=edge(u,v);
		}
	}
	return e;
}
