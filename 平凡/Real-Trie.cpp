#include<bits/stdc++.h>
#define MAXNODE 1008611
#define SIGMA 26
using namespace std;

namespace Trie{
	int ch[MAXNODE][SIGMA],val[MAXNODE],pool=1;
	
	inline int idx(char c){
		return c-'a';
	}
	
	inline void init(){
		memset(ch[0],0,sizeof ch[0]);
	}
	
	inline void insert(char *s,int info){
		int u=0,n=strlen(s);
		for(int i=0;i<n;++i){
			int v=idx(s[i]);
			if(!ch[u][v]){
				memset(ch[pool],0,sizeof ch[pool]);
				val[pool]=0,ch[u][v]=pool++;
			}
			u=ch[u][v];
		}
		val[u]=info;
	}
	
	inline find(char *s){
		int u=0,n=strlen(s);
		for(int i=0;i<n;++i){
			int v=idx(s[i]);
			if(!ch[u][v]) return 0;
			u=ch[u][v];
		}
		return val[u];
	}
}
