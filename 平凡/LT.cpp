#include<bits/stdc++.h>

int cnt=0;

struct node{
	int lc,rc,w,h;
}t[1008611];

int merge(int a,int b){
	if(!a) return b;
	if(!b) return a;
	
	if(t[a].w<t[b].w) std::swap(a,b);
	
	t[a].rc=merge(t[a].rc,b);
	//maintain(a);
	
	if(t[t[a].lc].h<t[t[a].rc].h) std::swap(t[a].lc,t[a].rc);
	
	if(t[a].rc) t[a].h=t[a].rc+1;
	else t[a].h=0;
	
	return a;
}

void insert(int a,int x){
	t[++cnt].w=x;
	merge(a,cnt);
}

void del(int a){
	merge(t[a].lc,t[a].rc);
}
