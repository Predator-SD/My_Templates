#include<bits/stdc++.h>
#define MAXN 20
#define MAXLOG 20
#define MAXNODE MAXN*MAXLOG
#define LOOP for(i=MAXLOG-1;i>=0;--i) 
using namespace std;
int ch[MAXNODE][2],size[MAXNODE],pool=2;
inline void ins(int x,int d=1){
	int i,u=1;bool v;
	LOOP{
		v=(x>>i)&1;
		if(!ch[u][v]) ch[u][v]=pool++;
		u=ch[u][v];
		size[u]+=d;
	}
}
inline int rank(int x){
	int i,u=1,res=0;bool v;
	LOOP{
		v=(x>>i)&1;
		if(v) res+=size[ch[u][0]];
		u=ch[u][v];
		if(!u) break;
	}
	return res;
}
inline int kth(int k){
	int i,u=1,res=0;
	LOOP{
		if(size[ch[u][0]]>=k) u=ch[u][0];
		else k-=size[ch[u][0]],u=ch[u][1],res|=(1<<i);
	}
	if(!u) return -1;
	return res;
}
