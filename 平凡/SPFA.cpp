#include<cstdio>
#include<queue>
using namespace std;
int dis[10086],w[10086][10086],pre[10086],G[10086][10086];
bool exist[10086];
queue<int>team;
void init(int s){
	dis[s]=0; exist[s]=true; team.push(s);
}
void SPFA(){
	while(team.size()!=0){
		int u=team.front(); team.pop(); exist[u]=false;
		for(int i=0;i<sizeof(G[u]);i++){
			int v=G[u][i];
			if(dis[v]>dis[u]+w[u][v]){
				dis[v]=dis[u]+w[u][v];
				pre[v]=u;
				if(!exist[v]){
					team.push(v); exist[v]=true;
				}
			}
		}
	}
}
