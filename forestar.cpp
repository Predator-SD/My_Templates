#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int head[1008611],k=1;
int a=0,b=0,c=0;
int s[10086];
struct edge{
	int to,next,w;
};
edge e[1008611];
inline void addedge(int u,int v,int w){
	e[k]=(edge){v,head[u],w};
	head[u]=k++;
}
void dfs(int p){
    s[p]=1;
    printf("%d|",p);
    for(int i=head[p];i!=-1;i=e[i].next){
        int v=e[i].to;
        if(s[v]==1) continue;
        else dfs(v);
    }
}
int main(){
	freopen("data.in","r",stdin);
	memset(head,-1,sizeof(head));
	memset(s,0,sizeof(s));
	while(a!=-1){
		scanf("%d%d%d",&a,&b,&c);
		addedge(a,b,c);
		addedge(b,a,c);
	}
	dfs(1);
	fclose(stdin);
	return 0;
}
