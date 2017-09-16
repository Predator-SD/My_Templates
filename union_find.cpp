#include<iostream>
using namespace std;

int n,m,p,r1,r2,r[5000];

//以下为压缩(误)路径并查集
struct node{
    int parent;
};
node t[5000];
int find(int x){
    return x==t[x].parent?t[x].parent:find(t[x].parent);
}
//以下为主函数
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>p;
    for(int i=0;i<n;i++){
        t[i].parent=i;
    }
    for(int i=0;i<m;i++){
        cin>>r1>>r2;
        t[find(r1)].parent=find(r2);
    }
    for(int i=0;i<p;i++){
        cin>>r1>>r2;
        if(t[find(r1)].parent==t[find(r2)].parent) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
