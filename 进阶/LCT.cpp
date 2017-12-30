#include<bits/stdc++.h>
#define maxn 200005

template<size_t MAXN>
struct Link_Cut_Tree{
	enum Relation{
		L=0,R=1
	};
	
	int ch[MAXN][2],pa[MAXN],siz[MAXN];
	bool rev[MAXN];
	
	int stk[MAXN],top;
	
	inline bool isrt(int x){
		return ch[pa[x]][L]!=x&&ch[pa[x]][R]!=x;
	}
	
	inline void pushdown(int x){
		if(rev[x]){
			rev[x]=false,
			
			std::swap(ch[x][L],ch[x][R]),
			rev[ch[x][L]]^=1,
			rev[ch[x][R]]^=1;
		}
	}
	
	inline void maintain(int x){
		siz[x]=siz[ch[x][L]]+siz[ch[x][R]]+1;
	}
	
	inline void rotate(int x){
		int y=pa[x],z=pa[y];
		bool l,r;
		
		l=ch[y][L]==x?L:R;
		r=l^1;
		
		if(!isrt(y)){
			if(y==ch[z][L]) ch[z][L]=x;
			else ch[z][R]=x;
		}
		
		pa[x]=z,pa[y]=x,
		pa[ch[x][r]]=y,
		ch[y][l]=ch[x][r],
		ch[x][r]=y,
		
		maintain(y),
		maintain(x);
	}
	
	inline void splay(int x){
		top=1,stk[top]=x;
		for(int i=x;!isrt(i);i=pa[i]) stk[++top]=pa[i];
		for(int i=top;i;--i) pushdown(stk[i]);
		
		while(!isrt(x)){
			int y=pa[x],z=pa[y];
			
			if(!isrt(y)){
				if((ch[y][L]==x)^(ch[z][L]==y)) rotate(x);
				else rotate(y);
			}
			rotate(x); 
		}
	}
	
	inline void access(int x){
		int t=0;
		while(x){
			splay(x);
			ch[x][R]=t;
			t=x,x=pa[x];
		}
	}
	
	inline void evert(int x){
		access(x),splay(x);
		rev[x]^=1;
	}
	
	inline void link(int x,int y){
		evert(x),pa[x]=y;
	}
	
	inline void cut(int x,int y){
		evert(x),access(y),splay(y);
		ch[y][L]=pa[x]=0;
	}
	
	inline void findrt(int x){
		access(x),splay(x);
		while(ch[x][L]) x=ch[x][L];
		return x;
	}
};

Link_Cut_Tree<maxn> T;
