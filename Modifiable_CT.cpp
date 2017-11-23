#include<cstdio>
#include<algorithm>

#define lowbit(x) (x&-x)
#define N 10005

int n,m;
int a[N],b[N<<1|1];

template<size_t maxn>
struct Modifiable_CT{
	enum Realtion{
		L=0,R=1
	};
	
	int sz,totx,toty,totn;
	int root[maxn];
	int xx[maxn],yy[maxn];
	int ch[maxn*600][2],size[maxn*600];
	
	void ins(int &o,const int &l,const int &r,const int pre,const int &k,const int &v){
		o=++sz;
		
		size[o]=size[pre]+v;
		ch[o][L]=ch[pre][L],ch[o][R]=ch[pre][R];
		
		if(l==r) return;
		const int mid=(l+r)>>1;
		if(k<=mid) ins(ch[o][L],l,mid,ch[pre][L],k,v);
		else ins(ch[o][R],mid+1,r,ch[pre][R],k,v);
	}
	
	void modify(const int &x,const int &v){
		int k=std::lower_bound(b+1,b+totn+1,a[x])-b;
		for(int i=x;i<=n;i+=lowbit(i)) ins(root[i],1,totn,root[i],k,v);
	}
	
	int query(const int &l,const int &r,const int &k){
		if(l==r) return l;
		
		int sum=0;
		const int mid=(l+r)>>1;
		
		for(int i=1;i<=totx;++i) sum-=size[ch[xx[i]][L]];
		for(int i=1;i<=toty;++i) sum+=size[ch[yy[i]][L]];
		
		if(k<=sum){
			for(int i=1;i<=totx;++i) xx[i]=ch[xx[i]][L];
			for(int i=1;i<=toty;++i) yy[i]=ch[yy[i]][L];
			return query(l,mid,k);
		}else{
			for(int i=1;i<=totx;++i) xx[i]=ch[xx[i]][R];
			for(int i=1;i<=toty;++i) yy[i]=ch[yy[i]][R];
			return query(mid+1,r,k-sum);
		}
	}
};

Modifiable_CT<N> MCT;



int ca[N],cb[N],cc[N];
inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}

int main(){
    register char s[20];
    n=read();m=read();
    for(register int i=1;i<=n;i++)a[i]=read(),b[++MCT.totn]=a[i];
    for(register int i=1;i<=m;i++){
        scanf("%s",s);ca[i]=read();cb[i]=read();
        if(s[0]=='Q')cc[i]=read();else b[++MCT.totn]=cb[i];
    }
    std::sort(b+1,b+MCT.totn+1);
    MCT.totn=std::unique(b+1,b+MCT.totn+1)-b-1;
    for(register int i=1;i<=n;i++) MCT.modify(i,1);
    for(register int i=1;i<=m;i++){
        if(cc[i]){
            MCT.totx=MCT.toty=0;
            for(register int j=ca[i]-1;j;j-=lowbit(j))MCT.xx[++MCT.totx]=MCT.root[j];
            for(register int j=cb[i];j;j-=lowbit(j))MCT.yy[++MCT.toty]=MCT.root[j];
            printf("%d\n",b[MCT.query(1,MCT.totn,cc[i])]);
        }
        else{MCT.modify(ca[i],-1);a[ca[i]]=cb[i];MCT.modify(ca[i],1);}
    }
}
