#include<cstdio>
#include<queue>

#define INF 0x3f3f3f3f
#define MAXN 10005
#define MAXM 100005

#define minn(a,b) ((a)<(b)?(a):(b))

int n,m;

struct Dinic{
    int s,t;
    
    int flow,cost;
    int cnt,head[MAXN],next[MAXM<<1|1];
    int dis[MAXN],cur[MAXN];
    
    std::queue<int> Q;
    
    struct Edge{
        int u,v,c,f;
        
        Edge(){}
        Edge(int u,int v,int c,int f):u(u),v(v),c(c),f(f){}
    }e[MAXM<<1|1];
    
    Dinic(){
        for(int i=0;i<MAXN;++i) head[i]=-1;
    }
    ~Dinic(){
        printf("%d\n",flow);
    }
    
    inline void addedge(int u,int v,int c){
        e[cnt]=Edge(u,v,c,0);
        next[cnt]=head[u];
        head[u]=cnt++;
        
        e[cnt]=Edge(v,u,0,0);
        next[cnt]=head[v];
        head[v]=cnt++;
    }
    
    inline bool BFS(){
        for(int i=0;i<=n;++i) dis[i]=0;
        dis[s]=1,Q.push(s);
        
        while(Q.empty()==false){
            int u=Q.front();
            Q.pop();
            
            for(int i=head[u];i!=-1;i=next[i]){
                Edge &ed=e[i];
                
                if(ed.c>ed.f&&dis[ed.v]==0)
                    dis[ed.v]=dis[u]+1,Q.push(ed.v);
            }
        }
        
        return dis[t];
    }
    
    int DFS(int u,int res){
        if(u==t||res==0) return res;
        
        int fff=0;
        for(int &i=cur[u];i!=-1;i=next[i]){
            Edge &ed=e[i];
            
            if(ed.c>ed.f&&dis[u]+1==dis[ed.v]){
                int f=DFS(ed.v,minn(ed.c-ed.f,res));
                
                fff+=f,res-=f;
                ed.f+=f,e[i^1].f-=f;
                
                if(res==0) break;
            }
        }
        
        return fff;
    }
    
    void solve(){
        while(BFS()){
            for(int i=0;i<=n;++i) cur[i]=head[i];
            flow+=DFS(s,INF);
        }
    }
};

Dinic a;

int main(){
    scanf("%d%d%d%d",&n,&m,&a.s,&a.t);
    
    register int x,y,z;
    for(register int i=0;i<m;++i){
        scanf("%d%d%d",&x,&y,&z);
        a.addedge(x,y,z);
    }
    
    a.solve();
    
    return 0;
}
