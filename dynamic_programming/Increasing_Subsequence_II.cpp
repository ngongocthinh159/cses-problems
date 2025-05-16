/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1748/
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
int segtree[4*N];
int merge(int &l, int &r) {
    int res = l + r;
    if (res >= MOD) res -= MOD;
    return res;
}
void update(int idx, int s, int e, int pos, int val) {
    if (s==e) {
        segtree[idx] += val;
        if (segtree[idx] >= MOD) segtree[idx] -= MOD;
        return;
    }
    int m = (s + e)/2;
    if (pos <= m)  
        update(2*idx, s, m, pos, val);
    else 
        update(2*idx + 1, m + 1, e, pos, val);
    segtree[idx] = merge(segtree[2*idx], segtree[2*idx + 1]);
}
int query(int idx, int s, int e, int l, int r) {
    if (s > r || l > e || s > e || l > r) return 0;
    if (l <= s && e <= r) return segtree[idx];
    int m = (s + e)/2;
    int l_ans = query(2*idx, s, m, l, r);
    int r_ans = query(2*idx + 1, m + 1, e, l, r);
    return merge(l_ans, r_ans);
}
void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    vector<int> a(n), arr(n);
    for (int i = 0; i < n; i++) cin >> a[i], arr[i] = a[i];
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    for (int i = 0; i < n; i++) {
        int idx = lower_bound(a.begin(), a.end(), arr[i]) - a.begin();
        arr[i] = idx + 1;
    }
    vector<int> dp(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = query(1, 0, n - 1, 0, arr[i] - 1);
        dp[i] += 1;
        if (dp[i] >= MOD) dp[i] -= MOD;
        ans += dp[i];
        if (ans >= MOD) ans -= MOD;
        update(1, 0, n - 1, arr[i], dp[i]);
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