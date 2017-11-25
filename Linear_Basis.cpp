#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const int l=100;

template<int MAXL>
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
};
