#include<bits/stdc++.h>
#define MAXN 100
using namespace std;
namespace trie {
    const int MAXLOG = 20 /* ÉÏÈ¡Õû(log(ÖµÓò´óÐ¡)) */;
    const int MAXNODE = MAXN * MAXLOG;
    int ch[MAXNODE][2], size[MAXNODE], pool = 2;
    inline void insert(int x, int d = 1) { //d = -1 ÎªÉ¾³ý
        int i, u = 1; bool v;
        for(i=MAXLOG-1;i>=0;i--) {
            v = (x >> i) & 1;
            if(!ch[u][v]) ch[u][v] = pool++;
            u = ch[u][v];
            size[u] += d;
        }
    }
    inline int rank(int x) {
        int i, u = 1, res = 0; bool v;
        for(i=MAXLOG-1;i>=0;i--) {
            v = (x >> i) & 1;
            if(v) res += size[ch[u][0]];
            u = ch[u][v];
            if(!u) break;
        }
        return res;
    }
    inline int kth(int k) {
        int i, u = 1, res = 0;
        for(i=MAXLOG-1;i>=0;i--) {
            if(size[ch[u][0]] >= k) u = ch[u][0];
            else k -= size[ch[u][0]], u = ch[u][1], res |= (1 << i);
        }
        if(!u) return -1;
        return res;
    }
}

//(1 << MAXLOG) - 1
int main(){
	//1 2 3 4  5  6  7
	//1 1 2 3 12 13 19
	trie::insert(13);
	trie::insert(12);
	trie::insert(19);
	trie::insert(2);
	trie::insert(3);
	trie::insert(1);
	trie::insert(1);

	cout<<trie::rank(1000)<<endl;
	
	return 0;
}
