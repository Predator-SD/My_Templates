#include<cstdio>
const int MAXN = 10000000;
const int MAXS = 60*1024*1024;
int numbers[MAXN];
char buf[MAXS];
void analyse(char *buf,int len = MAXS){
    int i;
    numbers[i=0]=0;
    for (char *p=buf;*p && p-buf<len;p++)
        if (*p == ' ') numbers[++i]=0;
        else numbers[i] = numbers[i] * 10 + *p - '0';
}
void fread_analyse(){
    freopen("data.txt","rb",stdin);
    int len = fread(buf,1,MAXS,stdin);
    buf[len] = '\0';
    analyse(buf,len);
}
