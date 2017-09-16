#include<iostream>
using namespace std;
typedef long long ll;
ll pow2(ll k,ll n){
    if(k==0) return 1;
    ll i=pow2(k/2,n);
    if(k%2==0){return (i*i)%n;}
    else{return (i*i*10)%n;}
}
int main(){
    ll n,m,k,x;
    cin>>n>>m>>k>>x;
    ll r=(((m%n)*pow2(k,n))%n+x%n)%n;
    cout<<r;
}
