#include<bits/stdc++.h>
#define minn(a,b) ((a)<(b)?(a):(b))
using namespace std;

int low[1008611],pre[1008611],dclock;
bool iscut[1008611];

int dfs(int u,int fa){
	int lowu=pre[u]=++dclock;
	int ch=0;
	
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		
		if(!pre[v]){
			int lowv=dfs(v,u);
			
			lowu=minn(lowu,lowv);
			
			if(lowv>=pre[u])
				iscut[u]=true;
		}
		else if(pre[v]<pre[u]&&v!=fa)
			lowu=minn(lowu,pre[v]);
	}
	
	if(fa<0&&ch==1) iscut[u]=0;
	
	return low[u]=lowu;
}
