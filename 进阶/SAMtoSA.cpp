#include<bits/stdc++.h>
#define MAXN 1008611
using namespace std;

template<size_t Sigma>
class SAM{
public:
	struct Node{
		Node *next,*ch[Sigma];
		int max;
		
		Node *fast;
		int flen;
		bool mark;
		
		Node(int maxx=0):ch(),next(NULL),max(maxx),mark(false),fast(NULL),flen(0){}
		
		inline int getMin(){
			return next->max+1;
		}
	}*root,*last;
	
	Node *pool[MAXN];
	int top=0;
	
	vector<int> sa;
	
	inline void prelude(){
		root=last=new Node;
		pool[++top]=root,
		pool[++top]=last;
	}
	
	inline Node *extend(int c){
		Node *u=new Node(last->max+1),*v=last;
		pool[++top]=u;
		for(;v&&!v->ch[c];v=v->next) v->ch[c]=u;
		
		if(!v)
			u->next=root;
		else if(v->ch[c]->max==v->max+1)
			u->next=v->ch[c];
		else{
			Node *n=new Node(v->max+1),*o=v->ch[c];
			pool[++top]=n;
			copy(o->ch,o->ch+Sigma,n->ch);
			n->next=o->next;
			o->next=u->next=n;
			for(;v&&v->ch[c]==o;v=v->next) v->ch[c]=n;
		}
		
		last=u;
		return u;
	}
	
	inline void label(){
		for(Node *u=last;u;u=u->next) u->mark=true;
	}
	
	void precalc(){
		for(int x=1;x<=top;++x){
			Node *p=pool[x];
			Node *q;
			int f=0;
			
			for(int i=0;i<Sigma;++i)
				if(p->ch[i]) ++f,q=p->ch[i];
			
			if(f==1&&!p->mark) p->fast=q,p->flen=1;
		}
	}
	
	Node* accelerate(Node *s){
		Node *p;
		int sum=0;
		
		for(p=s;p->fast;p=p->fast)
			sum+=p->flen;
			
		for(Node *q=s;q->fast;q=q->fast){
			sum-=q->flen;
			q->fast=p;
			q->flen+=sum;
		}
		
		return p;
	}
	
	void dfs(Node *u,int dis){
		if(u->mark) sa.push_back(dis);
		for(int i=0;i<Sigma;++i)
			if(u->ch[i]){
				Node *ac=u->ch[i];
				accelerate(ac);
				
				if(ac->fast) dfs(ac->fast,dis-1-ac->flen);
				else dfs(u->ch[i],dis-1);
			}
	}
	
	void build(int len){
		label();
		precalc();
		dfs(root,len);
	}
};

SAM<27> sss;
char buf[1008611];

int main(){
	scanf("%s",buf);
	int len=strlen(buf);
	sss.prelude(); 
	for(register int i=0;i<len;++i)
		sss.extend(buf[i]-'a');
	sss.build(len+1);
	for(register vector<int>::iterator it=sss.sa.begin()+1;it!=sss.sa.end();++it)
		printf("%d ",*it);
	return 0;
}
