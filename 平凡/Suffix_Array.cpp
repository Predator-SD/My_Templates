#include<bits/stdc++.h>
using namespace std;

template<size_t N>
class Suffix_Array{
public:
	int n;
	int sa[N+3],s[N+3];
	int rank[N+3],height[N+3];
	int cnt[N+3];
	
	struct bunch{
		int id,alpha,beta;
	}buc[N+3];
	
	inline static bool cmp(const bunch &lhs,const bunch &rhs){
		return (lhs.alpha<rhs.alpha)||(lhs.alpha==rhs.alpha&&lhs.beta<rhs.beta);
	}
	
	inline int idx(char s){
		if(s>='0'&&s<='9') return 1+s-'0';
		if(s>='A'&&s<='Z') return 11+s-'A';
		if(s>='a'&&s<='z') return 37+s-'a';
		return 63;
	}
	
	inline void read(char in[]){
		n=strlen(in);
		for(int i=0;i<n;++i) s[i]=idx(in[i]);
	}
	
	void radix_sort(){
		//sort(buc,buc+n,cmp);
		
		static bunch tmp[N+3];
		for(int i=0;i<N;++i) cnt[i]=0;
		for(int i=0;i<n;++i) ++cnt[buc[i].beta];
		for(int i=1;i<N;++i) cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;--i) tmp[--cnt[buc[i].beta]]=buc[i];
		for(int i=0;i<n;++i) buc[i]=tmp[i];
		
		for(int i=0;i<N;++i) cnt[i]=0;
		for(int i=0;i<n;++i) ++cnt[buc[i].alpha];
		for(int i=1;i<N;++i) cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;--i) tmp[--cnt[buc[i].alpha]]=buc[i];
		for(int i=0;i<n;++i) buc[i]=tmp[i];
		
	}
	
	void getSA(){
		bool ju[N+3],flag=true;
		for(int k=1;k<=n;k<<=1){
			memset(buc,0,sizeof buc);
			memset(ju,0,sizeof ju);
			
			for(int cur1=0,cur2=k;cur1<n;++cur1,++cur2)
				buc[cur1].id=cur1,
				buc[cur1].alpha=s[cur1],
				buc[cur1].beta=(cur2>=n?0:s[cur2]);
			radix_sort();
			
			for(int i=0,cnt=1;i<n;++i)
				cnt+=((i!=0)&&(buc[i].alpha!=buc[i-1].alpha||buc[i].beta!=buc[i-1].beta)),
				s[buc[i].id]=cnt;
			
			for(int i=0;i<n;++i)
				if(ju[s[i]]==0) ++ju[s[i]];
				else{flag=false; break;}
			if(flag==true) break;
			else flag=true;
		}
		
		for(int i=0;i<n;++i)
			sa[s[i]]=i;
	}
	
	void getHeight(){
		for(int i=0;i<=n;++i) rank[sa[i]]=i;
		
		for(int i=0,k=0;i<n;++i){
			if(k) --k;
			int j=sa[rank[i]-1];
			while(s[i+k]==s[j+k]) ++k;
			height[rank[i]]=k;
		}
	}
	
	void solve(char a[]){
		read(a),
		getSA();
		read(a),
		getHeight();
	}
};

Suffix_Array<1000005> sss;

char a[1000005];

int main(){
	scanf("%s",a);
	
	a[strlen(a)]='0';
	sss.solve(a);
	for(register int i=2;i<=sss.n;++i) printf("%d ",sss.sa[i]+1);
	puts("");
	for(register int i=3;i<=sss.n;++i) printf("%d ",sss.height[i]);
	return 0;
}
