/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1141/
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
    int a[n]{}, freq[n]{};
    for (int i = 0; i < n; i++) cin >> a[i];
    auto normalize = [&]() {
        int b[n];
        for (int i = 0; i < n; i++) b[i] = a[i];
        sort(b, b + n);
        int sz = unique(b, b + n) - b;
        for (int i = 0; i < n; i++)
            a[i] = lower_bound(b, b + sz, a[i]) - b;
    };
    normalize();
    int ans = -IINF;
    bool unique = true;
    for (int i = 0, l = 0; i < n; i++) { 
        if (++freq[a[i]] >= 2) unique = false;
        while (l < i && !unique) {
            if (--freq[a[l++]] == 1) unique = true;
        }
        ans = max(ans, i - l + 1);
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

