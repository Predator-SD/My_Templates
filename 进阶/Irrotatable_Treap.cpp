#include<bits/stdc++.h>
using namespace std;

class Treap{
public:
	enum Relation{
		L=0,R=1
	};
	
	struct Node{
		Node *ch[2];
		int key,val,size;
		
		Node(int v):key(rand()),val(v),size(1){ch[L]=ch[R]=NULL;}
		
		inline void maintain(){
			size=1+(ch[L]?ch[L]->size:0)+(ch[R]?ch[R]->size:0);
		}
	}*root;
	
	typedef pair<Node*,Node*> D;
	
	inline int size(Node *x){
		return x?x->size:0;
	}
	
	Node *merge(Node *a,Node *b){
		if(!a) return b;
		if(!b) return a;
		
		if(a->key<b->key){a->ch[R]=merge(a->ch[R],b); a->maintain(); return a;}
		else{b->ch[L]=merge(a,b->ch[L]); b->maintain(); return b;}
	}
	
	D split(Node *o,int k){
		if(!o) return D(NULL,NULL);
		
		D ans;
		if(size(o->ch[L])>=k){
			ans=split(o->ch[L],k);
			o->ch[L]=ans.second;
			o->maintain();
			ans.second=o;
		}else{
			ans=split(o->ch[R],k-size(o->ch[L])-1);
			o->ch[R]=ans.first;
			o->maintain();
			ans.first=o;
		}
		
		return ans;
	}
	
	int rank(Node *o,int v){
		if(o==NULL) return 0;
		return (o->val>=v)?rank(o->ch[L],v):rank(o->ch[R],v)+size(o->ch[L])+1;
	}
	
	int kth(int k){
		D x=split(root,k-1);
		D y=split(x.second,1);
		
		Node *ans=y.first;
		
		root=merge(merge(x.first,ans),y.second);
		
		return ans!=NULL?ans->val:0;
	}
	
	void ins(int v){
		int k=rank(root,v);
		D x=split(root,k);
		
		Node *o=new Node(v);
		root=merge(merge(x.first,o),x.second);
	}
	
	void del(int v){
		int k=rank(root,v);
		D x=split(root,k);
		D y=split(x.second,1);
		
		root=merge(x.first,y.second);
	}
}T;

int main(){
	int m,opt,x;
	scanf("%d",&m);
	
	while(m--){
		scanf("%d%d",&opt,&x);
		switch(opt){
            case 1:T.ins(x);break;
            case 2:T.del(x);break;
            case 3:printf("%d\n",T.rank(T.root,x)+1);break;
            case 4:printf("%d\n",T.kth(x));break;
            case 5:printf("%d\n",T.kth(T.rank(T.root,x)));break;
            case 6:printf("%d\n",T.kth(T.rank(T.root,x+1)+1));break;
        }
	}
	
	return 0;
}
