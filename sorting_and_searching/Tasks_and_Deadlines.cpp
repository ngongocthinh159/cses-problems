/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1630
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/


void pre_compute() {
    
}
void solve() {
    int n;
    cin >> n;
    int a[n], d[n];
    for (int i = 0; i < n; i++) cin >> a[i] >> d[i];
    int order[n];
    iota(order, order + n, 0);
    sort(order, order + n, [&](int i, int j) {
        return a[i] < a[j];
    });
    ll ans = 0, time = 0;
    for (int i = 0; i < n; i++) {
        int idx = order[i];
        time += a[idx];
        ans += d[idx] - time;
    }
    cout << ans << nline;
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    // cin >> T;
    pre_compute();
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}