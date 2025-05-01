/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1640/
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
    int n, x;
    cin >> n >> x;
    int a[200005], order[200005];
    for (int i = 0; i < n; i++) cin >> a[i];
    iota(order, order + n, 0);
    sort(order, order + n, [&](int i, int j) {
        return a[i] < a[j];
    });
    int i = 0, j = n - 1;
    bool found = false;
    while (i < j) {
        if (a[order[i]] + a[order[j]] > x) j--;
        else if (a[order[i]] + a[order[j]] < x) i++;
        else {
            cout << order[i] + 1 << " " << order[j] + 1 << nline;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "IMPOSSIBLE" << nline;
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