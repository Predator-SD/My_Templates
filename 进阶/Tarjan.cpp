#include<bits/stdc++.h>
#define minn(a,b) ((a)<(b)?(a):(b))
#define maxn 1008611
using namespace std;

int head[maxn],k=1;

struct edge{
	int to,next;
}e[maxn<<1|1];

int pre[maxn],low[maxn],sccno[maxn];
int dclock,cnt;

int S[maxn],top;

void dfs(int u){
	pre[u]=low[u]=++dclock;
	S[++top]=u;
	
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		
		if(!pre[v]){
			dfs(v);
			low[u]=minn(low[u],low[v]);
		}else if(!sccno[v])
			low[u]=minn(low[u],pre[v]);
	}
	
	if(low[u]==pre[u]){
		++cnt;
		
		while(true){
			int x=S[--top];
			sccno[x]=cnt;
			
			if(x==u) break;
		}
	}
}

void tarjan(const int &n){
	for(int i=0;i<n;++i)
		if(!pre[i])
			dfs(i);
}
