/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1651/
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

// segtree + lazy update
// oper 1: add val to all element in range [l, r]
// oper 2: query sum in range [l, r]
#define MAX 200005
struct Data {
    ll sum;
};
Data segtree[4*MAX];
ll lazy[4*MAX];
ll a[MAX];
Data make_data(ll sum) {
    Data res;
    res.sum = sum;
    return res;
}
Data merge(Data &l, Data &r) {
    Data res;
    res.sum = l.sum + r.sum;
    return res;
}
void build(int idx, int s, int e) {
    if (s == e) {
        segtree[idx] = make_data(a[s]);
        return;
    }
    int m = (s + e)/2;
    build(2*idx, s, m);
    build(2*idx + 1, m + 1, e);
    segtree[idx] = merge(segtree[2*idx], segtree[2*idx + 1]);
}
void apply(int idx, int s, int e, ll val) {
    segtree[idx].sum += val*(e - s + 1); // apply update
    lazy[idx] += val; // put tag
};
void push_down(int idx, int s, int e) {
    int m = (s + e)/2;
    apply(2*idx, s, m, lazy[idx]); // apply left child
    apply(2*idx + 1, m + 1, e, lazy[idx]); // apply right child
    lazy[idx] = 0; // reset lazy
}
void update(int idx, int s, int e, int l, int r, ll val) { // range update + val
    if (s > r || e < l) return;
    if (l <= s && e <= r) {
        apply(idx, s, e, val);
        return;
    }
    push_down(idx, s, e);
    int m = (s + e)/2;
    update(2*idx, s, m, l, r, val);
    update(2*idx + 1, m + 1, e, l, r, val);
    segtree[idx] = merge(segtree[2*idx], segtree[2*idx + 1]);
}
Data query(int idx, int s, int e, int l, int r) { // range sum query
    if (s > r || e < l) return make_data(0);
    if (l <= s && e <= r) return segtree[idx];
    push_down(idx, s, e);
    int m = (s + e)/2;
    Data l_ans = query(2*idx, s, m, l, r);
    Data r_ans = query(2*idx + 1, m + 1, e, l, r);
    return merge(l_ans, r_ans);
}

void pre_compute() {
    
}
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i< n; i++)cin>> a[i];
    build(1, 0, n - 1);
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t== 1) {
            int l, r, val; cin >> l >> r >> val;
            l--, r--;
            update(1, 0, n - 1, l, r, val);
        } else {
            int k; cin >> k;
            k--;
            cout << query(1, 0, n - 1, k, k).sum << nline;
        }
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