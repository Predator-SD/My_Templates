#include<cstdio>

int n;
double p[22],dp[1<<22|1];

double E(int s=0){
	if(s==(1<<n)-1) return 0;
	else if(dp[s]) return dp[s];
	
	double ans=1,foreward=0;
	for(int i=1,cnt=1;i<=1<<(n-1);i<<=1,++cnt)
		if(~s&i) ans+=p[cnt]*E(s|i),foreward+=p[cnt];
	
	return dp[s]=ans/foreward;
}

int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;++i) scanf("%lf",&p[i]);
	printf("%.3lf",E());
	return 0;
}
