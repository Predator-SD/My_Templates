#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int head[1008611],k=0;
int a=0,b=0,c=0;
struct edge{
	int to,next,w;
};
edge e[1008611];
inline void addedge(int u,int v,int w){
	e[k]=(edge){v,head[u],w};
	head[u]=k;
	k++;
}
inline void dfs(int x){
	for(int i=0;i<k;i++)    
        for(int j=head[i];j!=-1;j=e[j].next)    
            cout<<i<<" "<<e[j].to<<" "<<e[j].w<<endl;  
}
int main(){
	memset(head,-1,sizeof(head));
	while(a!=-1){
		scanf("%d%d%d",&a,&b,&c);
		addedge(a,b,c);
	}
	dfs(3);
	return 0;
}
