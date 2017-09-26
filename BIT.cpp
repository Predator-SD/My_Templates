#include<cstdio>
int n,m,c[500070],a[500070];
inline int lowbit(int i){
    return i&-i;
}
inline void add(int x,int d){
    while(x<=n){
        c[x]+=d;
        x+=lowbit(x);
    }
}
inline int sum(int x){
    int s=0;
    while(x){
        s+=c[x];
        x-=lowbit(x);
    }
    return s;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        add(i,a[i]);
    }
    for(int i=1;i<=m;i++){
        int c;scanf("%d",&c);
        if(c == 1){
            int x,k;
            scanf("%d%d",&x,&k);
            add(x,k);
        }else{
            int x,y;scanf("%d%d",&x,&y);
            printf("%d\n",sum(y)-sum(x-1));
        }
    }
    return 0;
}
