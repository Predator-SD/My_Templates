#include<bits/stdc++.h>
#define MAXN 10000005
using namespace std;

template<size_t Sigma>
struct SAM{
	struct Node{
		Node *next,*ch[Sigma];
		int max;
		
		Node(int max=0):max(max),next(NULL),ch(){}
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
			u->next=o->next=n;
			for(;v&&v->ch[c]==o;v=v->next) v->ch[c]=n;
		}
		
		last=u;
		return u;
	}
};

SAM<4> sss;

inline int idx(char ch){
    switch(ch){
        case 'N': return 0;
        case 'S': return 1;
        case 'W': return 2;
        case 'E': return 3;
        default: return -1;
    }
}

inline int solve(char *s){
    int len=strlen(s);
    SAM<4>::Node *v=sss.root;
    for (int i=0;i<len;++i){
        int c=idx(s[i]);
        if(v->ch[c]) v=v->ch[c];
        else return i;
    }
    return len;
}

int main(){
    int n,m;
    static char s[MAXN+1];
    scanf("%d %d\n%s",&n,&m,s);
    sss.prelude();
    for(register int i=0;i<n;++i)
        sss.extend(idx(s[i]));

    while(m--){
        static char s[MAXN+1];
        scanf("%s",s);
        printf("%d\n",solve(s));
    }
    
    return 0;
}
