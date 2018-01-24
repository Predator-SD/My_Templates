#include<bits/stdc++.h>
#define maxn 1008611
using namespace std;

struct edge{
	int to,next;
}e[maxn<<1|1];

int head[maxn],k,block[maxn],cnt;
int q[maxn],top,rt[maxn];

inline void addedge(int u,int v){
	e[++k]=(edge){v,head[u]},head[u]=k;
}

inline void add(int u,int v){
	addedge(u,v);
	addedge(v,u);
}

int n,b;

void dfs(int u,int pa){
	int curcnt=top;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v!=pa){
			dfs(v,u);
			if(top-curcnt>=b){
				block[++cnt]=u;
				for(;top>curcnt;--top) rt[q[top]]=cnt;
			}
		}
	}
	q[++top]=u;
}

int main(){
	scanf("%d%d",&n,&b);
	for(register int i=1;i<=n-1;++i){
		register int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	dfs(1,0);
	while(top) rt[q[top--]]=cnt;
	printf("%d\n",cnt);
	for(register int i=1;i<=n;++i) printf("%d ",rt[i]);puts("");
	for(register int i=1;i<=cnt;++i) printf("%d ",block[i]);puts("");
	return 0;
}
