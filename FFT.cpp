#include<cstdio>

#include <algorithm>
#include <complex>
#include <vector>
#include <cmath>

#define PI 3.141592653589793
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)

using namespace std;

typedef complex<double> Comp;

const Comp I(0,1);
const int MAX_N = 1 << 20;

Comp tmp[MAX_N];

void DFT(Comp *a,const int &n,const short &rev){
	if(n==1) return ;
	
	for(int i=0;i<n;++i) tmp[i]=a[i];
	
	for(int i=0;i<n;++i)
		if(i&1) a[(n>>1)+(i>>1)]=tmp[i];
		else a[i>>1]=tmp[i];
	
	Comp *a0=a;
	Comp *a1=a+(n>>1);
	DFT(a0,n>>1,rev);
	DFT(a1,n>>1,rev);
	
	Comp cur(1,0);
	const double alpha=PI*2/n*rev;
	Comp step=exp(I*alpha);
	
	for(int k=0;k<(n>>1);++k){
		tmp[k]=a0[k]+cur*a1[k];
		tmp[k+(n>>1)]=a0[k]-cur*a1[k];
		
		cur*=step;
	}
	
	for(int i=0;i<n;++i) a[i]=tmp[i];
}

int main() {
	static Comp a[1 << 20] = { }, b[1 << 20] = { };
	int n = 1 << 20;
	DFT(a, n, 1);
	DFT(b, n, 1);
	for (int i = 0; i < n; ++i) {
		a[i] *= b[i];
	}
	DFT(a, n, -1);
	for (int i = 0; i < n; ++i) {
		a[i] /= n;
	}
}
