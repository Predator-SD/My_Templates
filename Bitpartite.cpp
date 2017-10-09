#include<cstdio>
struct edge{
	int to,next;
}e[1008611];
int fa[1008611],k=1,color[1008611],head[1008611];
inline void addedge(int u,int v){
	e[k]=(edge){v,head[u]};
	head[u]=k++;
}
inline void add(int u,int v){
	addedge(u,v); addedge(v,u);
}
bool tu(int p){
	for(int i=head[p];i!=0;i=e[i].next){
        int v=e[i].to;
        if(color[v]==color[p]) return false;
        if(color[v]==0){
        	color[v]=3-color[p];
        	if(!tu(v)) return false;
		}
    }
    return true;
}
int main(){
	freopen("data.txt","r",stdin);
	int m;
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	color[1]=1;
	printf("%d",tu(1));
	fclose(stdin);
}
