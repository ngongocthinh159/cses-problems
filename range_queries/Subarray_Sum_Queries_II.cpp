/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/3226/
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)
#define MASK(i) (1LL << (i))
#define all(v) (v).begin(), (v).end()


template<class X, class Y>
bool minimize(X &x, const Y &y) {
    if (x > y) {
        x = y;
        return true;
    } else return false;
}
template<class X, class Y>
bool maximize(X &x, const Y &y) {
    if (x < y) {
        x = y;
        return true;
    } else return false;
}

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
struct chash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393
struct chashp {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(pair<uint64_t,uint64_t> x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);}}; // https://codeforces.com/blog/entry/62393
/*--------------------------------------------------------------------------------------------------------------------------*/

struct Data {
    ll mx, pref, surf, tot;
};
struct segtree {
    vector<Data> node;
    int n;
    segtree(vector<int> &arr) {
        n = arr.size();
        node.resize(4*n);
        build(1, 0, n - 1, arr);
    }
    Data merge(const Data &l, const Data &r) {
        Data res;
        res.tot = l.tot + r.tot;
        res.pref = max(l.pref, l.tot + r.pref);
        res.surf = max(r.surf, r.tot + l.surf);
        res.mx = INT_MIN;
        res.mx = max(res.mx, l.mx);
        res.mx = max(res.mx, r.mx);
        res.mx = max(res.mx, l.surf + r.pref);
        return res;
    }
    void build(int idx, int s, int e, vector<int> &arr) {
        if (s == e) {
            node[idx].mx = node[idx].pref = node[idx].surf = node[idx].tot = arr[s];
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    void update(int idx, int s, int e, int pos, int val) {
        if (s == e) {
            node[idx].mx = node[idx].pref = node[idx].surf = node[idx].tot = val;
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, val);
        else
            update(2*idx + 1, m + 1, e, pos, val);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    Data query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return Data{INT_MIN, INT_MIN, INT_MIN, 0};
        if (l <= s && e <= r) return node[idx];
        int m = (s + e)/2;
        return merge(query(2*idx, s, m, l, r),
                    query(2*idx + 1, m + 1, e, l, r));
    }
};
#define N 200005
int n, q;
void pre_compute() {
    
}
void solve() {
    cin >> n >> q;
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    segtree tree(x);
    int a, b;
    for (int i = 0; i < q; i++) {
        cin >> a >> b;
        a--, b--;
        cout << max(0LL, tree.query(1, 0, n - 1, a, b).mx) << nline;
    }
}

int main() {
    fastio();
    IN_OUT();
    int T = 1;
    pre_compute();
    // cin >> T;
    for (int cases = 1; cases <= T; cases++) {

        solve();
    }
    return 0;
}