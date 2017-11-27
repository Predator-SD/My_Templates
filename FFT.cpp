#include<cstdio>
#include<complex>

#define PI 3.141592653589793

using namespace std;

typedef complex<double> Comp;

const Comp I(0,1);
const int MAX_N = 1 << 10;

Comp tmp[MAX_N];

void FFT(Comp *a,const int &n,const short &rev){
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

template<typename T>
inline T poww(const T &a,const int &n){
	T ans=1;
	for(int i=0;i<n;++i) ans*=a;
	return ans;
}

int main() {
	static Comp a[1 << 10] = {1,2,3}, b[1 << 10] = {1,2,3};
	int n = 1 << 10;
	DFT(a, n, 1);
	DFT(b, n, 1);
	for (int i = 0; i < n; ++i) {
		a[i] *= b[i];
	}
	DFT(a, n, -1);
	for (int i = 0; i < n; ++i) {
		a[i] /= n;
	}
	
	double ans=0; 
	for(int i=0;i<10;++i) ans+=a[i].real()*poww(10,i);
	printf("%lf",ans);
}
