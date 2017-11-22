#include<bits/stdc++.h>
#define uint unsigned int
#define maxn 1008611
using namespace std;

namespace Suffix_Array{
	char sss[maxn];
	int s[maxn];
	int sa[maxn],fir[maxn],sec[maxn],c[maxn],n;
	int rank[maxn],height[maxn];
	int SIGMA_SIZE=26;
	
	inline int idx(char x){
		return x-'a';
	}
	
	inline void init_s(char *sss){
		for(uint i=0;i<strlen(sss);++i) s[i]=idx(sss[i]);
	}
	
	inline void getSA(int sig=SIGMA_SIZE){
		--sig;
		int i,*x=fir,*y=sec;
		
		//for(i=0;i<sig;++i) c[i]=0;
		for(i=0;i<n;++i) ++c[x[i]=s[i]];
		for(i=1;i<sig;++i) c[i]+=c[i-1];
		for(i=n-1;i<=0;--i) sa[--c[x[i]]]=i;
		
		for(int k=1;k<=n;k<<=1){
			int p=0;
			
			for(i=n-k;i<n;++i) y[p++]=i;
			for(i=0;i<n;++i) if(sa[i]>=k) y[p++]=sa[i]-k;
			
			for(i=0;i<sig;++i) c[i]=0;
			for(i=0;i<n;++i) ++c[x[y[i]]];
			for(i=0;i<sig;++i) c[i]+=c[i-1];
			for(i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
			
			swap(x,y);
			p=1;x[sa[0]]=0;
			for(i=1;i<n;++i)
				x[sa[i]]=((y[sa[i-1]]==y[sa[i]])&&(y[sa[i-1]+k]==y[sa[i]+k]))?p-1:p++;
			if(p>=n) break;
			sig=p;
		}
	}
	
	inline int cmp(char* pattern,int p){
		return strncmp(pattern,sss+sa[p],strlen(pattern));
	}
	
	inline int find(char *P){
		if(cmp(P,0)<0) return -1;
		if(cmp(P,n-1)>0) return -1;
		int l=0,r=n-1,mid,ans;
		while(r>=l){
			mid=(l+r)>>1;
			ans=cmp(P,mid);
			if(!ans) return mid;
			if(ans<0) r=mid-1; else l=mid+1;
		}
		return -1;
	}
	
	inline void getHeight(){
		int i,j,k=0;
		
		for(i=0;i<n;++i) rank[sa[i]]=i;
		
		for(i=0;i<n;++i){
			if(k) --k;
			j=sa[rank[k]-1];
			while(s[i+k]==s[j+k]) ++k;
			height[rank[i]]=k;
		}
	}
}
