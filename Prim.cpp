#include <bits/stdc++.h>

using namespace std;
const int INF = 1e8;
typedef long long ll;

int n;
int x[5010],y[5010];

double dist( int x1 , int y1 , int x2 , int y2 ){
    ll x = x1 - x2;
    ll y = y1 - y2;
    return sqrt( x*x + y*y );
}

double prim(){
    bool vis[5010];
    double d[5010];
    double result = 0;
    memset( vis , false , sizeof(vis) );
    vis[0] = true;
    for( int i = 0 ; i < n ; ++i ) d[i] = dist( x[0] , y[0] , x[i] , y[i] );
    d[0] = INF;
    
    for( int i = 0 ; i < n-1 ; ++i ){
        int u = min_element( d , d+n ) - d;
        result += d[u];
        d[u] = INF;
        vis[u] = true;
        for( int v = 0 ; v < n ; ++v ){
            if( vis[v] == false ){
                double dis = dist( x[u] , y[u] , x[v] , y[v] );
                if( dis < d[v] ){
                    d[v] = dis;
                }
            }
        }
    }
    return result;
}

int main(){
    cin >> n;
    for( int i = 0 ; i < n ; ++i ){
        cin >> x[i] >> y[i];
    }
    printf( "%.2lf\n" , prim() );
    return 0;
}
