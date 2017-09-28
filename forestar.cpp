#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
int head[1008611],k=1,dco=-1;
int a,b,c,fa[1008611];
bool s[1008611];
vector<int> D,E,B,bfs;
queue<int> t;
struct edge{
	int to,next,w;
};
edge e[1008611];
inline init(){
	memset(head,-1,sizeof(head));
	memset(s,false,sizeof(s));
}
inline bfsinit(int u){
	t.push(u);
}
inline void addedge(int u,int v,int w=1){
	e[k]=(edge){v,head[u],w};
	head[u]=k++;
}
void DEB(int p){
    s[p]=true;
    D.push_back(p);
    E.push_back(p);
    B.push_back(++dco);
    for(int i=head[p];i!=-1;i=e[i].next){
        int v=e[i].to;
        if(s[v]==true) continue;
        else DEB(v);
        E.push_back(p);
        B.push_back(--dco);
    }
}
void BFS(){
	while(t.size()){
		int p=t.front();
		t.pop();
		bfs.push_back(p);
		for(int i=head[p];i!=-1;i=e[i].next){
			int v=e[i].to;
			if(v!=fa[p]&&!fa[v]){
				fa[v]=p;
				t.push(v);
			}
		}
	}
}
int main(){ 
	freopen("data.in","r",stdin);
	init();
	while(a!=-1){
		scanf("%d%d%d",&a,&b,&c);
		addedge(a,b,c);
		addedge(b,a,c);
	}
	fclose(stdin);
	 
	/*
	DEB(1);
	for(int i=0;i<D.size();i++) printf("%d|",D[i]);
	printf("\n");
	for(int i=0;i<E.size();i++) printf("%d|",E[i]);
	printf("\n");
	for(int i=0;i<B.size();i++) printf("%d|",B[i]);
	*/
	
	/*
	bfsinit(1);
	BFS();
	for(int i=0;i<bfs.size();i++) printf("%d|",bfs[i]);
	return 0;
	*/
}
