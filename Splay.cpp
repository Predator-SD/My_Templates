#include<bits/stdc++.h>
#define MIN 0x80000000
#define MAX 0x7fffffff
#define uint unsigned int
using namespace std;

template<typename T>
struct Splay{
	struct node_t{
		T val;
		node_t *lc,*rc,*pa,**root;
		uint size;
		
		node_t(const T &val,node_t *pa,node_t **root):val(val),pa(pa),lc(NULL),rc(NULL),size(1),root(root){}
		~node_t(){if(lc) delete lc; if(rc) delete rc;}
		
		inline node_t *grandparent(){return !pa?NULL:pa->pa;}
		inline node_t *&child(uint x){return !x?lc:rc;}
		inline uint relation(){return this==pa->lc?0:1;}
		inline void maintain(){size=lsize()+rsize()+1;}
		inline uint lsize(){return lc?lc->size:0;}
		inline uint rsize(){return rc?rc->size:0;}
		
		inline void rotate(){
    		node_t *old=pa;
    		uint x=relation();
    		if(grandparent())
        		grandparent()->child(old->relation())=this;
    		pa=grandparent();
    		old->child(x)=child(x^1);
    		if (child(x^1))
        		child(x^1)->pa=old;
    		child(x^1)=old;
    		old->pa=this;
    		old->maintain();
    		maintain();
    		if(!pa)
        		*root=this;
		}
		
		inline node_t *splay(node_t **target=NULL){
    		if(!target) target=root;
    		while(this!=*target){
        		if (pa==*target) rotate();
        		else if(relation()==pa->relation())
            		pa->rotate(), rotate();
        		else rotate(),rotate();
    		}
    		return *target;    
		}
		
		inline node_t *pred(){
			node_t *pred=this;
			while(pred->val==this.val){
				pred->splay();
				pred=pred->lc;
				while(pred->rc) pred=pred->rc;
			}
			return pred->splay();
		}
		
		inline node_t *succ(){
			node_t *succ=this;
			while(succ->val==this->val){
				succ->splay();
				succ=succ->rc;
				while(succ->lc) succ=succ->lc;
			}
			return succ->splay();
		}
	}*root;
	
	Splay():root(NULL){
    	insert(MIN);
    	insert(MAX);
	}
	
	inline node_t *insert(const T &value){
    	node_t **target=&root,*parent=NULL;
    	while(*target){
        	parent=*target;
        	parent->size++;
        	if(value<(*target)->value) target=&(*target)->lchild;
        	else target=&(*target)->rchild;
    	}
    	*target=new node_t(value,parent,&root);
    	return (*target)->splay();
	}
	
	inline node_t *find(const T &value){
    	node_t *node=root;
    	while(node&&value!=node->val)
        	if(value<node->val) node=node->lc;
        	else node=node->rc;
    	if(node) return node->pred()->succ()->splay();
    	else return NULL;
	}
	
	inline uint rank(const T &value){return find(value)->lsize();}
	
	inline const T &pred(const T &value){
    	node_t *node=find(value);
    	if(node) return node->pred()->value;
    	else{
        	node=insert(value);
        	const T &result=node->pred()->value;
        	erase(node);
        	return result;
    	}
	}

	inline const T &succ(const T &value) {
    	node_t *node=find(value);
    	if(node) return node->succ()->value;
    	else{
        	node=insert(value);
        	const T &result=node->succ()->value;
        	erase(node);
        	return result;
    	}
	}
	
	inline void erase(const T &value){
    	node_t *node=find(value);
    	erase(node);
	}

	inline void erase(const T &l,const T &r){
    	erase(find(l),find(r));
	}

	inline void erase(node_t *l,node_t *r=NULL){
    	if(!r) r=l;
    	node_t *pred=l->pred();
    	node_t *succ=r->succ();
    	pred->splay();
    	succ->splay(&pred->rc);
    	delete succ->lc;
    	succ->lchild = NULL;
    	succ->maintain();
    	pred->maintain();
	}
};
