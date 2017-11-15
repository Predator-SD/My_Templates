#include<bits/stdc++.h>
#define uint unsigned int
#define maxn 1008611
#define MAX 0x7fffffff
#define MIN 0x80000000
using namespace std;

template<typename T>
struct Splay{
	struct node{
		T val;
		node *lc,*rc,*pa,**root;
		uint size;
		
		node(const T &val,node *pa,node **root):val(val),pa(pa),lc(NULL),rc(NULL),size(1),root(root){}
		~node(){if(lc) delete lc; if(rc) delete rc;}
		
		inline node *grandpa(){return !pa?NULL:pa->pa;}
		inline node *&child(bool r){return r==0?lc:rc;}
		inline bool relation(){return this==pa->lc?0:1;}
		inline void maintain(){size=lsize()+rsize()+1;}
		inline uint rsize(){return rc->size;}
		inline uint lsize(){return lc->size;}
		
		inline void rot(){
			bool r=relation();
			node *opa=pa;
			
			if(grandpa())
			    grandpa()->child(opa->relation())=this;
			pa=grandpa();
			
			opa->child(r)=child(r^1);
			if(child(r^1)) child(r^1)->pa=opa;
			
			child(r^1)=opa;
			opa->pa=this;
			
			opa->maintain();
			maintain();
			if(!pa) *root=this;
		}
		
		inline node *splay(node **target){
			if(!target) target=root;
			while(this!=*root){
				if(pa==*target) rot();
				else if(relation()==pa->relation()) pa->rot(),rot();
				else rot(),rot();
			}
			return *target;
		}
		
		inline node *pred(){
			node *pred=this;
			while(pred->val==this->val){
				pred->splay();
				pred=pred->lc;
				while(pred->rc) pred=pred->rc;
			}
			return pred->splay();
		}
		
		inline node *succ(){
			node *succ=this;
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
	
	inline uint rank(const T &value){return find(value)->lsize();}
	
	inline node *insert(const T &value){
		node **target=&root,*parent=NULL;
		while(*target){
			parent=*target;
			++parent->size();
			if(value<(*target)->val) target=&(*target)->lc;
			else target=&(*target)->rc;
		}
		*target=new node(value,parent,&root);
		return *target->splay();
	}
	
	inline node *find(uint value){
		node *node=root;
		while(node&&value!=node->val)
		    if(value<node->val) node=node->lc;
		    else node=node->rc;
		if(node) return node->splay();
		else return NULL;
	}
	
	inline const T &pred(const T &value){
		node *node=find(value);
		if(node) return node->pred()->val;
		else{
			node=insert(value);
			const T &result=node->pred()->val;
			erase(node);
			return result;
		}
	}
	
	inline void erase(node *l,node *r=NULL){
		if(!r) r=l;
		node *pred=l->pred();
		node *succ=r->succ();
		pred->splay();
		succ->splay(&pred->rc);
		delete succ->lc;
		succ->lc=NULL;
		succ->maintain();
		pred->maintain();
	}
	
	inline void erase(const T &l,const T &r){
		erase(find(l),find(r));
	}
	
	inline void erase(const T &k){
		erase(find(k));
	}
};
