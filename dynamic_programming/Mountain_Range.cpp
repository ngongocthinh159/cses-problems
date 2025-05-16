/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/3314/
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
void build(int idx, int s, int e) {
    if (s== e ) {
        segtree[idx] = -IINF;
        return;
    }
    int m = (s + e)/2;
    build(2*idx, s, m);
    build(2*idx + 1,m + 1, e);
}
void update(int idx, int s, int e, int pos, int val) {
    if (s==e) {
        segtree[idx] = val;
        return;
    }
    int m = (s + e)/2;
    if (pos <= m)  
        update(2*idx, s, m, pos, val);
    else 
        update(2*idx + 1, m + 1, e, pos, val);
    segtree[idx] = max(segtree[2*idx], segtree[2*idx + 1]);
}
int query(int idx, int s, int e, int l, int r) {
    if (s > r || l > e || s > e || l > r) return -IINF;
    if (l <= s && e <= r) return segtree[idx];
    int m = (s + e)/2;
    int l_ans = query(2*idx, s, m, l, r);
    int r_ans = query(2*idx + 1, m + 1, e, l, r);
    return max(l_ans, r_ans);
}
void pre_compute() {
    
}
void solve() {
    int n; cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> st;
    vector<int> L(n), R(n), dp(n);
    for (int i = 0; i < n; i++) {
        while (st.size() && a[st.back()] < a[i]) st.pop_back();
        if (st.size())
            L[i] = st.back();
        else
            L[i] = -1;
        st.push_back(i);
    } 
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (st.size() && a[st.back()] < a[i]) st.pop_back();
        if (st.size())
            R[i] = st.back();
        else
            R[i] = n;
        st.push_back(i);
    }
    int order[n];
    iota(order, order + n, 0);
    sort(order, order + n, [&](int i, int j) {
        return a[i] < a[j];
    });
    build(1, 0, n - 1);
    int ans = 0;
    for (int idx = 0; idx < n; idx++) {
        int i = order[idx];
        int l1 = L[i] + 1, r1 = i - 1;
        int l2 = i + 1, r2 = R[i] - 1;
        int mx = 0;
        if (l1 <= r1) mx = max(mx, query(1, 0, n - 1, l1, r1));
        if (l2 <= r2) mx = max(mx, query(1, 0, n - 1, l2, r2));
        dp[i] = 1 + mx;
        ans = max(ans, dp[i]);
        update(1, 0, n - 1, i, dp[i]);
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