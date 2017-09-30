#include<cstdio>
#include<cstring>
typedef unsigned long long ull;
int main(){
        freopen("data.in","r",stdin);
	//variables
	register int n,m,g,i,p;
	scanf("%d%d",&n,&m);
	register int e[n],an[3*m+1];
	memset(e,0,sizeof(e)); memset(an,0,sizeof(an));
	//init
	for(g=0;g<n;g++)
	    for(i=0;i<m;i++){
	    	scanf("%d",&p);
	    	if(p==0) e[g]+=(0<<(3*m));
	    	if(p==1) e[g]+=(1<<(3*m));
	    	if(p==2) e[g]+=(3<<(3*m));
	    	if(p==3) e[g]+=(7<<(3*m));
	    }
        fclose(stdin);
	//calculate    
	for(g=0;g<n;g++)
	    for(i=g+1;i<n;i++)
	        an[__builtin_popcount(e[g]^e[i])]+=2;
	//output
	for(i=0;i<3*m+1;i++) printf("%d ",an[i]);
	return 0;
}
