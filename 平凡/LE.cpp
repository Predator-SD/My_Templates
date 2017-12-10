#include<cstdio>
int tot,prime[1008611],phi[1008611];
bool mark[1008611];
inline void euler(int N){
	phi[1]=1;
	int i,j;
	for(i=2;i<=N;++i){
		if(!mark[i]){
		    prime[++tot]=i;
		    phi[i]=i-1;
	    }
	    for(j=1;j<=tot;++j){
	    	if(i*prime[j]>N) break;
	    	mark[i*prime[j]]=true;
	    	if(!(i%prime[j])){
	    		phi[i*prime[j]]=phi[i]*prime[j];
	    		break;
			}else phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}
