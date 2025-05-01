/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/result/12761398/
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

#define N 3005
int k, n, a[N];
vector<ll> dp, ndp;
ll pref[N];
void pre_compute() {
    
}
ll C(int l, int r) {
    ll res = pref[r + 1] - pref[l];
    return res * res;
}
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;
    
    int mid = l + r >> 1;
    pair<ll,int> best = {LINF, -1};
    
    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k - 1 >= 0 ? dp[k - 1] : 0) + C(k, mid), k});
    }

    ndp[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
void solve() {
    cin >> n >> k;
    dp.resize(n);
    ndp.resize(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
        dp[i] = pref[i + 1] * pref[i + 1];
    }
    for (int i = 2; i <= k; i++) {
        compute(0, n - 1, 0, n - 1);
        swap(dp, ndp);
    }
    cout << dp[n - 1] << nline;
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