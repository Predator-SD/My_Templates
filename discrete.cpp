#include <cstring>
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;
const int MAXN = 100010;

int n, a[MAXN], b[MAXN];

namespace Discrete {
	int *p[MAXN*2], sz;
	void addnum( int *ptr ) {
		p[sz++] = ptr;
	}
	bool cmp( int *i, int *j ) {
		return *i < *j;
	}
	void solve() {
		sort(p, p+sz, cmp);
		int last = *p[0], id = 1;
		for( int i = 0; i < sz; ++i )
			if( *p[i] == last ) *p[i] = id;
			else last = *p[i], *p[i] = ++id;
	}
}

int main() {
	cin >> n;
	for( int i = 0; i < n; ++i ) cin >> a[i];
	for( int i = 0; i < n; ++i ) cin >> b[i];
	for( int i = 0; i < n; ++i )
		Discrete::addnum( a+i );
	for( int i = 0; i < n; ++i )
		Discrete::addnum( b+i );
	Discrete::solve();
	for( int i = 0; i < n; ++i ) cout << a[i] << " ";
	cout << endl;
	for( int i = 0; i < n; ++i ) cout << b[i] << " ";
	cout << endl;
	return 0;
}
