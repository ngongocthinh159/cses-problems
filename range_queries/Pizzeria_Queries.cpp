/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/2206/
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

#define data Data
struct data {
    ll a, b;
};
struct segtree {
    vector<data> node;
    int n;
    segtree(vector<int>&arr) {
        n = arr.size();
        node.resize(4*n);
        build(1, 0, n - 1, arr);
    }
    data merge(const data &l, const data &r) {
        data res;
        res.a = min(l.a, r.a);
        res.b = min(l.b, r.b);
        return res;
    }
    void build(int idx, int s, int e, vector<int> &arr) {
        if (s == e) {
            node[idx].a = arr[s] + s;
            node[idx].b = arr[s] - s;
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    void update(int idx, int s, int e, int pos, int val) {
        int m = (s + e)/2;
        if (s == e) {
            node[idx].a = val + s;
            node[idx].b = val - s;
            return;
        }
        if (pos <= m)
            update(2*idx, s, m, pos, val);
        else
            update(2*idx + 1, m + 1, e, pos, val);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    data query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return data{LINF, LINF};
        if (l <= s && e <= r) return node[idx];
        int m = (s + e)/2;
        return merge(query(2*idx, s, m, l, r),
                    query(2*idx + 1, m + 1, e, l, r));
    }
};
int n, q;
void pre_compute() {
    
}
void solve() {
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    segtree tree(arr);
    int t, k, x;
    for (int i = 0; i < q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> k >> x;
            k--;
            tree.update(1, 0, n - 1, k, x);
        } else {
            cin >> k;
            k--;
            ll res = LINF;
            if (k - 1 >= 0) {
                res = min(res, tree.query(1, 0, n - 1, 0, k - 1).b + k);
            }
            res = min(res, tree.query(1, 0, n - 1, k, n - 1).a - k);
            cout << res << nline;
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