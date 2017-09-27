#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int head[1008611],k=1,dco=0;
int a=0,b=0,c=0;
int s[10086];
vector<int> D,E,B;
struct edge{
	int to,next,w;
};
edge e[1008611];
inline init(){
	memset(head,-1,sizeof(head));
	memset(s,0,sizeof(s));
}
inline void addedge(int u,int v,int w){
	e[k]=(edge){v,head[u],w};
	head[u]=k++;
}
void DEB(int p){
    s[p]=1;
    D.push_back(p);
    E.push_back(p);
    B.push_back(dco);
    for(int i=head[p];i!=-1;i=e[i].next){
        int v=e[i].to;
        if(s[v]==1) continue;
        else{
		    dco++; DEB(v);
	    }
	    dco--;
        E.push_back(p);
        B.push_back(dco);
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
	DEB(1);
	for(int i=0;i<D.size();i++) printf("%d|",D[i]);
	printf("\n");
	for(int i=0;i<E.size();i++) printf("%d|",E[i]);
	printf("\n");
	for(int i=0;i<B.size();i++) printf("%d|",B[i]);
	return 0;
}
