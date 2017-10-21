#include<cstdio>
#define mod 1000000007
#define ll long long
struct mat{
  ll v[2][2];
};
inline mat qmul(mat a,mat b){
  mat c;
  for(int i=0;i<2;++i)
    for(int j=0;j<2;++j)
      c.v[i][j]=(a.v[i][0]*b.v[0][j]+a.v[i][1]*b.v[1][j])%mod;
  return c;
}
inline ll qf(int n){
  if(n==0||n==1) return n;
  mat c,ans;
  c.v[0][0]=c.v[0][1]=c.v[1][0]=1,c.v[1][1]=0;
  memset(ans.v,0,sizeof ans.v),ans.v[0][0]=1;
  --n;
  while(n){
    if(n&1) ans=qmul(ans,c);
    c=qmul(c,c);
    n>>=1;
  }
  return ans.v[0][0];
}
int main(){
  register int n;
  scanf("%d",&n);
  printf("%lld",qf(n+1));
  return 0;
}
