/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1736/
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

#define data _d
struct segtree {
    vector<ll> node;
    vector<pair<ll,ll>> lazy;
    int n;
    segtree(vector<int> &arr) {
        n = arr.size();
        node.resize(4*n);
        lazy.resize(4*n);
        build(1, 0, n - 1, arr);
    }
    ll merge(const ll &l, const ll &r) {
        return l + r;
    }
    void build(int idx, int s, int e, vector<int>&arr) {
        if (s == e) {
            node[idx] = arr[s];
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    void apply(int idx, int s, int e, ll u1, ll d) {
        ll len = e - s + 1;
        node[idx] += len * u1 + d * (len - 1) * len / 2;
        lazy[idx].first += u1;
        lazy[idx].second += d;
    }
    void push_down(int idx, int s, int e) {
        if (lazy[idx].first) {
            int m = (s + e)/2;
            apply(2*idx, s, m, lazy[idx].first, lazy[idx].second);
            apply(2*idx + 1, m + 1, e, lazy[idx].first + (m - s + 1) * lazy[idx].second, lazy[idx].second);
            lazy[idx].first = 0;
            lazy[idx].second = 0;
        }
    }
    int inter_len(int x1, int y1, int x2, int y2) {
        if (x1 > y2 || x2 > y1) return 0;
        return min(y1, y2) - max(x1, x2) + 1;
    }
    void update(int idx, int s, int e, int l, int r, ll val) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            apply(idx, s, e, val, 1);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, val);
        update(2*idx + 1, m + 1, e, l, r, val + inter_len(s, m, l, r)); // be careful, the update(2*idx, s, m, l, r, val) not always update the whole segment [s, m]
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    ll query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return node[idx];
        push_down(idx, s, e);
        int m = (s + e)/2;
        return merge(query(2*idx, s, m, l, r),
                    query(2*idx + 1, m + 1, e, l, r));
    }
};
void pre_compute() {
    
}
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    int t, a, b;
    segtree tree(arr);
    for (int i = 0; i < q; i++) {
        cin >> t >> a >> b;
        a--, b--;
        if (t == 1) {
            tree.update(1, 0, n - 1, a, b, 1);
        } else {
            cout << tree.query(1, 0, n - 1, a, b) << nline;
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