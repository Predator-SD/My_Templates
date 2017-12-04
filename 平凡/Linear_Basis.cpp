#include<cstdio>
#include<algorithm>
#define ull unsigned long long
using namespace std;

const int MAXL=100;

struct Linear_Basis{
	ull a[MAXL+3];
	
	Linear_Basis(){
		fill(a,a+MAXL+1,0);
	}
	~Linear_Basis(){
		delete a;
	}
	
	inline void ins(ull t){
		for(int i=MAXL;i>=0;--i){
			if(!(t&(111<<i))) continue;
			
			if(a[i]) t^=a[i];
			else{
				for(int j=0;j<i;++j) if(t&(111<<j)) t^=a[j];
				for(int j=i+1;j<=MAXL;++j) if(a[j]&(111<<i)) a[j]^=t;
				
				a[i]=t;
				return ;
			}
		}
	}
	
	inline void mergefrom(const Linear_Basis &rhs){
		for(int i=0;i<MAXL;++i) ins(rhs.a[i]);
	}
};

inline Linear_Basis merge(const Linear_Basis &a,const Linear_Basis &b){
	Linear_Basis c=a;
	for(int i=0;i<MAXL;++i) c.ins(b.a[i]);
	
	return c;
}
