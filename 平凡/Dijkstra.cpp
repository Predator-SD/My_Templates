#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

template<typename T>
inline void read(T &x){
  char ch;while((ch=getchar()),(ch>'9'||ch<'0'));
  x=ch-'0';while((ch=getchar()),(ch>='0'&&ch<='9')) x=x*10+ch-'0';
}

struct edge{
	int to,next,w;
}e[500003];
int head[10003],k=1;
int d[10003];
bool vis[10003];

inline void addedge(int u,int v,int w){
	e[k]=(edge){v,head[u],w},head[u]=k++;
}

struct hnode{
	int d,u;
	inline bool operator < (const hnode &rhs) const{
		return d>rhs.d;
	}
};

priority_queue<hnode> heap;

inline void DIJ(int s){
	heap.push((hnode){0,s});
	hnode t;int i;
	while(heap.size()){
		t=heap.top(),heap.pop();
		if(vis[t.u]) continue;
		vis[t.u]=true;
		for(i=head[t.u];i;i=e[i].next) if(d[t.u]+e[i].w<d[e[i].to]) d[e[i].to]=d[t.u]+e[i].w,heap.push((hnode){d[e[i].to],e[i].to});
	}
}

int main(){
	register int i,n,m,s,u,v,w;
	read(n),read(m),read(s);
	memset(d,INF,sizeof d);
	d[s]=0;
	for(i=0;i<m;++i) read(u),read(v),read(w),addedge(u,v,w);
	DIJ(s);
	for(i=1;i<=n;++i) if(d[i]>=INF) printf("%d ",0x7fffffff); else printf("%d ",d[i]);
	return 0;
} 
