#include<bits/stdc++.h>
#define maxn 10086
using namespace std;

int head[maxn],headT[maxn],k,kT;

struct edge{
	int to,next;
}e[maxn<<1|1],eT[maxn<<1|1];

bool vis[maxn];
int sccno[maxn],cnt;
int S[maxn],top;

void dfs1(int u){
	if(vis[u]) return ;
	
	vis[u]=true;
	for(int i=head[u];i;i=e[i].next)
		dfs1(e[i].to);
	
	S[++top]=u;
}

void dfs2(int u){
	if(sccno[u]) return ;
	
	sccno[u]=cnt;
	for(int i=headT[u];i;i=eT[i].next)
		dfs2(eT[i].to);
}

void solve(int n){
	for(int i=0;i<n;++i)
		dfs1(i);
	
	for(int i=n;i>0;--i)
		if(!sccno[S[i]])
			dfs2(S[i]);
}
