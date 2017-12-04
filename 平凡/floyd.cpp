#include<cstdio>
#include<algorithm>
int n,w[10086][10086];
void floyd(){
	for(int k=1;k<=n;k++)
	    for(int i=1;i<=n;i++)
	        for(int j=1;j<=n;j++)
	            if(w[i][j]>w[i][k]+w[k][j]) w[i][j]=w[i][k]+w[k][j];
}
void floyd2(){
	for(int k=1;k<=n;k++)
	    for(int i=1;i<=n;i++)
	        for(int j=1;j<=n;j++)
	            w[i][j]=w[i][j]||(w[i][k]&&w[k][j]);
}
