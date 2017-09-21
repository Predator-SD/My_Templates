#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int en;
struct edge{
	int w,fr,to;
};
struct set{
    int parent;
};
set t[10086];
edge e[10086],A[10086];
int find(int u){
	return u==t[u].parent?u:find(t[u].parent);
}
bool cmp(edge a,edge b){
	if(a.w<=b.w) return true;
	else return false;
}
void kruskal(){
	int c=0;
	sort(e,e+en,cmp);
	for(int i=0;i<en;i++){
		edge p=e[i];
		if(find(p.fr)!=find(p.to)){
			A[c]=p;
			c++;
			t[find(p.fr)].parent=find(p.to);
		}
	}
}
