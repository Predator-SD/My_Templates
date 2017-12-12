#include<cstdio>
#include<cstring>
#include<algorithm>

#define minn(a,b) ((a)<(b)?(a):(b))
#define maxx(a,b) ((a)>(b)?(a):(b))

#define maxn 1008611

using namespace std;

char s1[maxn+5],s2[(maxn<<1)+5];
int n,len,r[(maxn<<1)+5];

inline void prelude(){
    n=strlen(s1),
    
    s2[++len]='@',
    s2[++len]='$';
    
    for(int i=0;i<n;++i)
        s2[++len]=s1[i],
        s2[++len]='$';
    
    s2[len+1]='\0';
}

inline void manacher(){
    int cur=0,right=0;
    
    for(int i=1;i<=len;++i){
        int x=right<i?1:minn(right-i,r[(cur<<1)-i]);
        
        while(s2[i+x]==s2[i-x]) ++x;
        
        cur=(i+x>right)?i:cur,
        right=(i+x>right)?(i+x):right,
		  
        r[i]=x;
    }
}
