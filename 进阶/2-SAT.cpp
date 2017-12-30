#include<bits/stdc++.h>
using namespace std;

template<size_t MAXN>
struct Two_SAT{
	int n;
	int S[MAXN<<1|1],c;
	bool mark[MAXN<<1|1];
	vector<int> G[MAXN<<1|1];
	
	Two_SAT(const int &n):n(n){memset(mark,false,sizeof mark);}
	
	bool dfs(int x){
		if(mark[x]) return true;
		if(mark[x^1]) return false;
		
		mark[x]=true;
		S[c++]=x;
		
		for(int i=0;i<G[x].size();++i)
			if(!dfs(G[x][i])) return false;
		return true;
	}
	
	bool solve(){
		for(int i=0;i<n*2;i+=2)
			if(!mark[i]&&!mark[i+1]){
				c=0;
				if(!dfs(i)){
					while(c>0) mark[S[--c]]=false;
					if(!dfs(i+1)) return false;
				}
			}
		return true;
	}
};

int main(){
	
	return 0;
}
