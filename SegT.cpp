#include<cstdio>
#include<algorithm>
class Segment_Tree{
public:
	int n,bit,d[1008611];
	inline int opt(int a,int b);
    inline void build(){
    	scanf("%d",&n);
        for(bit=1;bit<=n+1;bit<<=1);
        for(int i=bit+1;i<=bit+n;i++) scanf("%d",&d[i]);
        for(int i=bit-1;i;i--) d[i]=opt(d[i<<1],d[i<<1|1]);
    }
    inline void update(int x,int y){
        for(d[x+=bit]=y,x>>=1;x;x>>=1) d[x]=opt(d[x<<1],d[x<<1|1]);
    }
    inline int qquery(int l,int r,int ans=0){
        for(l+=bit-1,r+=bit+1;l^r^1;l>>=1,r>>=1){
            if(~l&1) ans=opt(ans,d[l^1]);
            if(r&1) ans=opt(ans,d[r^1]);
        }
        return ans;
    }
    inline int query(int x){
    	return d[bit+x];
    }
}seg;
inline int Segment_Tree::opt(int a,int b){return std::max(a,b);}

int main(){
	seg.build();
	seg.update(1,5);
	seg.update(2,9);
	seg.update(3,2);
	printf("%d",seg.query(2));
}
