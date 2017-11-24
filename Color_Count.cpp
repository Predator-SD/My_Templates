#include<cstdio>
#include<map>
#define N 100001

template<typename T>
inline void read(T &x){
  char ch;while((ch=getchar()),(ch>'9'||ch<'0'));
  x=ch-'0';while((ch=getchar()),(ch>='0'&&ch<='9')) x=x*10+ch-'0';
}

template<size_t maxn>
struct Chairman_Tree{
	enum Relation{
		L=0,R=1
	};
	
	int root[maxn*20],index;
	int ch[maxn*20][2],val[maxn*20];
	
	Chairman_Tree():index(0){
		//memset(root,0,sizeof root);
		//memset(ch,0,sizeof ch);
		//memset(val,0,sizeof val);
	}
	
	inline void pushup(const int &o){
		val[o]=val[ch[o][L]]+val[ch[o][R]];
	}
	
	void build(int &o,const int &l,const int &r){
		o=index++;
		
		if(l==r){
			val[o]=0;
			return ;
		}
		
		const int mid=(l+r)>>1;
		build(ch[o][L],l,mid);
		build(ch[o][L],mid+1,r);
	}
	
	void update(int &o,const int pre,const int &l,const int &r,const int &pos,const int &v){
		o=index++;
		
		ch[o][L]=ch[pre][L],ch[o][R]=ch[pre][R];
		val[o]=val[pre];
		
		if(l==pos&&r==pos){
			val[o]+=v;
			return ;
		}
		
		const int mid=(l+r)>>1;
		if(pos<=mid) update(ch[o][L],ch[pre][L],l,mid,pos,v);
		else update(ch[o][R],ch[pre][R],mid+1,r,pos,v);
		
		pushup(o);
	}
	
	int query(const int &o,const int &l,const int &r,const int &pos){
		if(l==r) return val[o];
		
		const int mid=(l+r)>>1;
		if(pos<=mid) return val[ch[o][R]]+query(ch[o][L],l,mid,pos);
		else return query(ch[o][R],mid+1,r,pos);
	}
};

Chairman_Tree<N> CT;
std::map<int,int> mp;
int b[N];

int main(){
	register int n,m,x,y;
	read(n);
	
	for(register int i=1;i<=n;++i) read(b[i]);
	CT.build(CT.root[0],1,n);
	
	for(register int i=1;i<=n;++i){
		if(mp.find(b[i])==mp.end())
			CT.update(CT.root[i],CT.root[i-1],1,n,i,1);
		else{
			int tmp;
			CT.update(tmp,CT.root[i-1],1,n,mp[b[i]],-1);
			CT.update(CT.root[i],tmp,1,n,i,1);
		}
		mp[b[i]]=i;
	}
	
	read(m);
	for(register int i=0;i<m;++i){
		read(x),read(y);
		printf("%d\n",CT.query(CT.root[y],1,n,x));
	}
}
