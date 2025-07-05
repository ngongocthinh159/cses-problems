/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1647/
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define MASK(x) (1LL << (x))

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 200005
#define LOG 19
int n, q;
int rmq[LOG + 1][N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        rmq[0][i] = x;
    }
    for (int j = 1; j <= LOG; j++)
        for (int i = 0; i + MASK(j) - 1 < n; i++)
            rmq[j][i] = min(rmq[j - 1][i], rmq[j - 1][i + MASK(j - 1)]);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--, r--;
        int msb = 32 - __builtin_clz(r - l + 1) - 1;
        cout << min(rmq[msb][l], rmq[msb][r - MASK(msb) + 1]) << nline;
    }
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