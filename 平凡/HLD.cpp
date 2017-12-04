#include<cstdio>
#define max 1008611
int head[max],k=1,siz[max],top[max],son[max],fa[max],deep[max];
struct edge{
	int to,next;
}e[max];
inline void addedge(int u,int v){
	e[k]=(edge){v,head[u]},head[u]=k++;
}
void dfs1(int u){
	deep[u]=deep[fa[u]]+1,siz[u]=1;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v!=fa[u]&&!fa[v]){
		    fa[v]=u;
		    dfs1(v);
		    siz[u]+=siz[v];
		    if(siz[son[u]]<siz[v]) son[u]=v;
	    }
	}
}
void dfs2(int u){
	if(u==son[fa[u]])top[u]=top[fa[u]];
	else top[u]=u;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(fa[v]==u) dfs2(v);
	}
}
inline void init(int u){
	dfs1(u),dfs2(u);
}
inline int query(int x,int y){
	for(;top[x]!=top[y];deep[top[x]]>deep[top[y]]?x=fa[top[x]]:y=fa[top[y]]);
	return deep[x]>deep[y]?y:x;
}
int n,m,x,y,s;
int main(){
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<n;i++){
        scanf("%d%d",&x,&y);addedge(x,y);addedge(y,x);
    }
    init(s);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
    }
    return 0 ;
}
