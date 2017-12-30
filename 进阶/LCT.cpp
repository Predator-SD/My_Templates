#include<bits/stdc++.h>
#define maxn 1000005
using namespace std;

template<size_t MAXN>
struct Link_Cut_Tree{
    enum Relation{
        L=0,R=1
    };
    
    int ch[MAXN][2],pa[MAXN];
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
        ch[x][r]=y; 
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
    
    inline void reverse(int x){
        access(x),splay(x);
        rev[x]^=1;
    }
    
    inline void link(int x,int y){
        reverse(x),pa[x]=y,splay(x);
    }
    
    inline void cut(int x,int y){
        reverse(x),access(y),splay(y);
        ch[y][L]=pa[x]=0;
    }
    
    inline int findrt(int x){
    	access(x),splay(x);
    	while(ch[x][L]) x=ch[x][L];
    	return x;
	}
};

Link_Cut_Tree<maxn> T;

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int n,m;

int main(){
    char ch[10];
    int x,y;
    n=read(),m=read();
    for(register int i=1;i<=m;++i){
        scanf("%s",ch);
        x=read(),y=read();
        if(ch[0]=='C') T.link(x,y);
        else if(ch[0]=='D') T.cut(x,y);
        else{
            if(T.findrt(x)==T.findrt(y)) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
