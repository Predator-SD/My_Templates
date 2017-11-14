#include<cstdio>
#include<cstring>
using namespace std;

namespace KMP{
	inline void getfail(char* P,int* f){
		int m=strlen(P),j;
		f[0]=f[1]=0;
		for(int i=1;i<m;++i){
			j=f[i];
			while(j&&P[i]!=P[j]) j=f[j];
			f[i+1]=(P[i]==P[j]?j+1:0);
		}
	}

	inline void KMP(char* T,char* P,int* f){
		int n=strlen(T),m=strlen(P),j=0;
		getfail(P,f);
		for(int i=0;i<n;++i){
		    while(j&&T[i]!=P[j]) j=f[j];
		    if(T[i]==P[j]) ++j;
		    if(j==m) printf("%d\n",i-m+1);
	    }
    }
}
