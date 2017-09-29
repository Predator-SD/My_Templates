#include<cstdio>
inline int tt(int a,int w){
	if(w==100) return a/100;
	else if(w==10) return a/10-(a/100)*10;
	else return a-tt(a,100)*100-tt(a,10)*10;
}
inline int ttb(int i){
	int g=tt(i,1),s=tt(i,10),b=tt(i,100);
	if(g!=s&&g!=b&&s!=b){
		return (1<<g)+(1<<s)+(1<<b);
	}else return -1;
}
int main(){
	for(int i=123;i<=329;i++){
		int b=i*2,c=i*3,x=ttb(i),y=ttb(b),z=ttb(c);
		if(x!=-1&&y!=-1&&z!=-1&&(x&y)==0&&(x&z)==0&&(y&z)==0)
		    printf("%d %d %d\n",i,b,c);
	}
	return 0;
}

