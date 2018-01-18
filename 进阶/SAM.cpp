#include<bits/stdc++.h>
#define uint unsigned int
using namespace std;

template<size_t Sigma>
class SAM{
public:
	struct Node{
		Node *next,*ch[Sigma];
		uint max;
		
		Node(const int maxx):ch(),next(NULL),max(maxx){}
		
		inline uint getMin(){
			return next->max+1;
		}
	}*root,*last;
	
	inline void prelude(){
		root=last=new Node;
	}
	
	inline Node *extend(int c){
		Node *u=new Node(last->max+1),*v=last;
		for(;v&&!v->ch[c];v=v->next) v->ch[c]=u;
		
		if(!v)
			u->next=root;
		else if(v->ch[c]->max==v->max+1)
			u->next=v->ch[c];
		else{
			Node *n=new Node(v->max+1),*o=v->ch[c];
			copy(o->ch,o->ch+Sigma,n->ch);
			n->next=o->next;
			o->next=u->next=n;
			for(;v&&v->ch[c]==o;v=v->next) v->ch[c]=n;
		}
		
		last=u;
		return u;
	}
};
