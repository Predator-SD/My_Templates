#include<cstdio>
#include<iostream>
#define N 42000
using namespace std;
int next[N],to[N],head[N],num,deep[N],father[N][21],n,m,p,a,b,c;
inline void add(int false_from,int false_to){
    next[++num]=head[false_from];
    to[num]=false_to;
    head[false_from]=num;
}
void dfs(int x){
    deep[x]=deep[father[x][0]]+1;
    for(int i=0;father[x][i];i++)
        father[x][i+1]=father[father[x][i]][i];
    for(int i=head[x];i;i=next[i])
        if(!deep[to[i]]){
            father[to[i]][0]=x;
            dfs(to[i]);
        }
}
inline int lca(int x,int y){
    if(deep[x]>deep[y])
        swap(x,y);
    for(int i=20;i>=0;i--)
        if(deep[father[y][i]]>=deep[x])
            y=father[y][i];
    if(x==y)
        return y;
    for(int i=20;i>=0;i--)
        if(father[y][i]!=father[x][i]){
            y=father[y][i];
            x=father[x][i];
        }
    return father[x][0];
}
int main(){
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<n;++i){
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
    }
    dfs(p);
    for(int i=1;i<=m;++i){
        scanf("%d%d",&a,&b);
        printf("%d ",lca(a,b));
    }
    return 0;
}
