/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1750/
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


#define N 200005
#define LOG 29
int n, q;
int par[LOG + 1][N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> par[0][i];
    }
    for (int j = 1; j <= LOG; j++)
        for (int i = 1; i <= n; i++) 
            par[j][i] = par[j - 1][par[j - 1][i]];
    for (int i = 0; i < q; i++) {
        int x, k; cin >> x >> k;
        for (int bit = LOG; bit >= 0; bit--) {
            if ((k>>bit)&1)
                x = par[bit][x];
        }
        cout << x << nline;
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