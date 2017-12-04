#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int d[10086][10086];
void init(const vector<int> A){
    int n=A.size();
    for(int i=0;i<n;i++) d[i][0]=A[i];
    for(int j=1;(1<<j)<=n;j++)
        for(int i=0;i+(1<<j)-1<n;i++)
            d[i][j]=min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
}
int RMQ(int L,int R){
    int k=0;
    while((1<<k)<R-L+1) k++;
    return min(d[L][k],d[R-(1<<k)+1][k]);
}

int main(){
    vector<int> e;
    e.push_back(1);
    e.push_back(2);
    e.push_back(-3);
    e.push_back(7);
    e.push_back(1);
    e.push_back(8);
    e.push_back(-1);
    e.push_back(2);
    e.push_back(0);
    e.push_back(9);
    init(e);
    int a,b,r;
    while(1){
        scanf("%d%d",&a,&b);
        r=RMQ(a,b);
        printf("%d",r);
    }
    return 0;
}
