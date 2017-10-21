#include<cstdio>
#define ll long long
#define mod 998244353
#define maxn 4000003
template<typename T>
inline void read(T &x){
  char ch;while((ch=getchar()),(ch>'9'||ch<'0'));
  x=ch-'0';while((ch=getchar()),(ch>='0'&&ch<='9')) x=x*10+ch-'0';
}
inline int qadd(int x,int y){
  int re=x+y;
  if(re>=mod) re-=mod;
  return re;
}
inline int qmul(ll x,ll y){return x*(y%mod)%mod;}
struct node{
  int parent;
}t[maxn];
int p[maxn],op[maxn],ans;
ll sum[maxn];
bool flag[maxn];
ll maxx;
inline int find(int x){
  return t[x].parent==x?x:find(t[x].parent);
}
inline void unio(int x,int y){
  sum[find(x)]+=sum[find(y)];
  t[find(y)].parent=find(x);
  maxx=sum[find(x)]>maxx?sum[find(x)]:maxx;
}
int main(){
  register int n,i;
  read(n);
  for(i=1;i<=n;++i) read(p[i]),t[i].parent=i,sum[i]=p[i];
  for(i=n;i>=1;--i) read(op[i]);
  for(i=1;i<n;++i){
    flag[op[i]]=true,maxx=sum[op[i]]>maxx?sum[op[i]]:maxx;
    if(flag[op[i]-1]) unio(op[i]-1,op[i]);
    if(flag[op[i]+1]) unio(op[i]+1,op[i]);
    ans=qadd(ans,qmul(qmul(n-i,n-i),maxx));
  }
  printf("%d\n",ans);
  return 0;
}
