#include<bits/stdc++.h>
#define maxn 1008611
#define maxm 10086
using namespace std;

template<size_t SIZE>
struct MemoryPool{
	char buf[SIZE],*cur;
	
	MemoryPool():cur(buf){}
	
	inline void *alloc(const int size){
		if(cur==buf+SIZE) return malloc(size);
		else{
			char *p=cur;
			cur+=size;
			return p;
		}
	}
};

MemoryPool<(4+4+8+8+4)*maxn*10> pool;

struct Chairman_Tree{
	struct Node{
		int l,r;
		Node *lc,*rc;
		int cnt;
		
		Node(const int l,const int r,Node *lc=NULL,Node *rc=NULL):l(l),r(r),lc(lc),rc(rc),cnt((lc?lc->cnt:0)+(rc?rc->cnt:0)){};
		Node(const int l,const int r,const int cnt):l(l),r(r),lc(NULL),rc(NULL),cnt(cnt){};
		
		inline void pushdown(){
			if(lc&&rc) return ;
			
			const int mid=(l+r)>>1;
			if(!lc) lc=new (pool.alloc(sizeof(Node))) Node(l,mid);
			if(!rc) rc=new (pool.alloc(sizeof(Node))) Node(mid+1,r);
		}
		
		Node *insert(const int val){
			if(val<l||val>r) return this;
			else if(val==l&&val==r) return new (pool.alloc(sizeof(Node))) Node(l,r,this->cnt+1);
			else{
				const int mid=(l+r)>>1;
				pushdown();
				if(val<=mid) return new (pool.alloc(sizeof(Node))) Node(l,r,lc->insert(val),rc);
				else return new (pool.alloc(sizeof(Node))) Node(l,r,lc,rc->insert(val));
			}
		}
		
		inline int rank() const {
			return lc?lc->cnt:0;
		} 
	}*root[maxn+1];
	
	int n;
	
	void build(const int a[],const int n){
		this->n=n;
		root[0]=new (pool.alloc(sizeof(Node))) Node(0,n-1);
		for(int i=1;i<=n;++i) root[i]=root[i-1]->insert(a[i-1]);
	}
	
	int query(const int l,const int r,int k){
		Node *L=root[l-1],*R=root[r];
		int min=0,max=n-1;
		while(min!=max){
			L->pushdown(),R->pushdown();
			int mid=(max+min)>>1,t=R->rank()-L->rank();
			if(k<=t) L=L->lc,R=R->lc,max=mid;
			else k-=t,L=L->rc,R=R->rc,min=mid+1;
		}
		return min;
	}
}t;

int n, m, a[maxn];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    static int set[maxn];
    copy(a, a + n, set);
    sort(set, set + n);
    int *end = unique(set, set + n);
    for (int i = 0; i < n; i++) a[i] = lower_bound(set, end, a[i]) - set;

    t.build(a, n);

    for (int i = 0; i < m; i++) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        int ans = t.query(l, r, k);
        printf("%d\n", set[ans]);
    }

    return 0;
}
