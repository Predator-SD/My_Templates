#include<cstdio>
#define uint unsigned int
#define MAXN 1008611
#define MAX 0x7fffffff
using namespace std;

template<typename T,T INF>
struct Splay{
	enum Relation{
		L=0,R=1
	};
	
	struct Node{
		Node *ch[2],*pa,**root;
		T val;
		uint size,cnt;
		
		Node(const T &value,Node *parent,Node **root):pa(parent),root(root),val(value),cnt(1){
			ch[L]=ch[R]=NULL;
		}
		~Node(){
			if(ch[L]) delete ch[L];
			if(ch[R]) delete ch[R];
		}
		
		inline Relation relation(){return this==pa->ch[L]?L:R;}
		
		inline void maintain(){size=(ch[L]?ch[L]->size:0)+(ch[R]?ch[R]->size:0)+cnt;}
		
		inline void rot(){
			Relation r=relation();
			Node *old=pa;
			
			if(old->pa) old->pa->ch[pa->relation()]=this;
			pa=old->pa;
			
			old->ch[r]=ch[r^1];
			if(ch[r^1]) ch[r^1]->pa=old;
			
			ch[r^1]=old;
			old->pa=this;
			
			maintain();
			old->maintain();
			
			if(!pa) *root=this;
		}
		
		inline Node *splay(Node *tarpa=NULL){
			while(pa!=tarpa){
				if(pa->pa==tarpa) rot();
				else if(relation()==pa->relation()) pa->rot(),rot();
				else rot(),rot();
			}
			return this;
		}
		
		inline Node *pred(){
			splay();
			Node *v=ch[L];
			while(v->ch[R]) v=v->ch[R];
			return v;
		}
		
		inline Node *succ(){
			splay();
			Node *v=ch[R];
			while(v->ch[L]) v=v->ch[L];
			return v;
		}
		
		inline uint rank(){
			return ch[L]?ch[L]->size:0;
		}
	}*root;
	
	Splay():root(NULL){
		insert(INF),insert(-INF);
	}
	~Splay(){
		delete root;
	}
	
	inline Node *find(const T &x){
		Node *v=root;
		
		while(v&&v->val!=x){
			if(x<v->val) v=v->ch[L];
			else v=v->ch[R];
		}
		
		return v?v->splay():NULL;
	}
	
	inline Node *insert(const T &x){
		Node *v=find(x);
		
		if(v){
			++v->cnt,v->maintain();
			return v;
		}
		
		Node **target=&root,*parent=NULL;
		while(*target){
			parent=*target;
			++parent->size;
			if(x<parent->val) target=&parent->ch[L];
			else target=&parent->ch[R];
		}
		
		*target=new Node(x,parent,&root);
		return (*target)->splay();
	}
	
	inline void erase(Node *v){
		if(!v) return ;
		
		if(v->cnt!=1){
			v->splay();
			--v->cnt;
			v->maintain();
			return ;
		}
		
		Node *pred=v->pred();
		Node *succ=v->succ();
		pred->splay();
		succ->splay(pred);
		
		delete succ->ch[L];
		succ->ch[L]=NULL;
		
		succ->maintain();
		pred->maintain();
	}
	
	inline void erase(const T &value){
		erase(find(value));
	}
	
	inline uint rank(const T &value){
        Node *v=find(value);
        if(v) return v->rank();
        else{
            v=insert(value);
            uint ans=v->rank();
            erase(v);
            return ans;
        }
    }
    
    inline Node *select(uint k){
    	++k;
    	Node *v=root;
    	while(v->rank()+1>k||v->rank()+v->cnt<k){
    		if(k<v->rank()+1) v=v->ch[L];
    		else k-=v->rank()+v->cnt,v=v->ch[R];
		}
		return v->splay();
	}
	
	inline Node *select(uint l,uint r){
		Node *lbound=select(l-1);
		Node *rbound=select(r+1);
		
		lbound->splay();
		rbound->splay(lbound);
		
		return rbound->ch[L];
	}
	
	inline const T &pred(const T &value){
		Node *v=find(value);
		if(v) return v->pred()->val;
		v=insert(value);
		const T &result=v->pred()->val;
		erase(v);
		return result;
	}
	
	inline const T &succ(const T &value){
		Node *v=find(value);
		if(v) return v->succ()->val;
		v=insert(value);
		const T &result=v->succ()->val;
		erase(v);
		return result;
	}
};

int n;
Splay<int,MAX> splay;

void dfs(Splay<int,MAX>::Node *v, int depth) {
    if (v->ch[Splay<int,MAX>::L]) dfs(v->ch[Splay<int,MAX>::L], depth + 1);
    for (int i = 0; i < depth; i++) {
        putchar(' ');
    }
    printf("%d\n", v->val);
    if (v->ch[Splay<int,MAX>::R]) dfs(v->ch[Splay<int,MAX>::R], depth + 1);
}

void print() {
    dfs(splay.root, 0);
    puts("--------------------------------------------------");
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int command, x;
        scanf("%d %d", &command, &x);
        if (command == 1) {
            splay.insert(x);
        } else if (command == 2) {
            splay.erase(x);
        } else if (command == 3) {
            printf("%d\n", splay.rank(x));
        } else if (command == 4) {
            printf("%d\n", splay.select(x)->val);
        } else if (command == 5) {
            printf("%d\n", splay.pred(x));
        } else if (command == 6) {
            printf("%d\n", splay.succ(x));
        }
    }

    return 0;
}
