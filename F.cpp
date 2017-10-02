#include<cstdio>
#include<cstring>
int re[2097152],te[2097152];
class FWT{
public:
    inline void fwt(int *a, int n){
        for(int d = 1; d < n; d <<= 1){
            for(int m = d<<1, i = 0; i < n; i += m){
                for(int j = 0; j < d; j++){
                    int x = a[i+j], y = a[i+j+d];
                    a[i+j] = x+y; a[i+j+d] = x-y;
                }
            }
        }
    }
    inline void ufwt(int *a, int n){
        for(int d = 1; d < n; d <<= 1){
            for(int m = d<<1, i = 0; i < n; i += m){
                for(int j = 0; j < d; j++){
                    int x = a[i+j], y = a[i+j+d];
                    a[i+j] = (x+y)/2; a[i+j+d] = (x-y)/2;
                }
            }
        }
    }
    inline void cal(int *a, int *b, int n){
        fwt(a, n);
        fwt(b, n);
        for(int i = 0; i < n; i++) a[i] *= b[i];
        ufwt(a, n);
    }
}fwt;
inline int swi(int m){
	if(m==1) return 8;
	if(m==2) return 64;
	if(m==3) return 512;
	if(m==4) return 4096;
	if(m==5) return 32768;
	if(m==6) return 262144;
	if(m==7) return 2097152;
	if(m==8) return -1;
	if(m==9) return -1;
}
int main(){
        //freopen("data.in","r",stdin);
	//variables
	register int n,m,g,i,p;
	scanf("%d%d",&n,&m);
	register int e=0,an[3*m+1],nn=swi(m);
	if(nn==-1){
		printf("Fuck");
		return 0;
	}
	memset(an,0,sizeof(an)); memset(re,0,sizeof(re));
	//init
	for(g=0;g<n;g++){
	    for(i=0;i<m;i++){
	    	scanf("%d",&p);
	    	if(p==0) e+=(0<<(3*i));
	    	if(p==1) e+=(1<<(3*i));
	    	if(p==2) e+=(3<<(3*i));
	    	if(p==3) e+=(7<<(3*i));
	    }
	    re[e]+=1;
	    e=0;
        }
        //fclose(stdin);
        memcpy(te,re,sizeof(re));
	//calculate   
	fwt.cal(re,te,nn); 
	for(e=0;e<nn;e++){
		an[__builtin_popcount(e)]+=re[e];
	}
	//output
	for(i=0;i<3*m+1;i++) printf("%d ",an[i]);
	return 0;
}
