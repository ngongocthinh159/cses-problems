/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1735/
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

#define data _D
struct data {
    ll val;
};
enum lazytype {
    EMPTY,
    SET,
    INCR
};
struct segtree {
    vector<data> node;
    vector<ll> lazyv;
    vector<lazytype> lazyt;
    int n;
    segtree(vector<int> &arr) {
        n = arr.size();
        node.resize(4*n);
        lazyv.resize(4*n);
        lazyt.assign(4*n, lazytype::EMPTY);
        build(1, 0, n - 1, arr);
    }
    data merge(const data &l, const data &r) {
        data res;
        res.val = l.val + r.val;
        return res;
    }
    void build(int idx, int s, int e, vector<int> &arr) {
        if (s == e) {
            node[idx].val = arr[s];
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    void apply(int idx, int s, int e, lazytype t, ll val) {
        if (t == lazytype::SET) {
            node[idx].val = (e - s + 1) * val;
            lazyt[idx] = t;
            lazyv[idx] = val;

            // merge lazy => No need to merge

        } else if (t == lazytype::INCR) {
            node[idx].val += (e - s + 1) * val;

            // merge lazy
            if (lazyt[idx] == lazytype::EMPTY) {
                lazyt[idx] = lazytype::INCR;
                lazyv[idx] = val;
            } else if (lazyt[idx] == lazytype::INCR) {
                lazyv[idx] += val;
            } else if (lazyt[idx] == lazytype::SET) {
                lazyv[idx] += val;
            }
        }
    }
    void push_down(int idx, int s, int e) {
        if (lazyt[idx] != lazytype::EMPTY) {
            int m = (s + e)/2;
            apply(2*idx, s, m, lazyt[idx], lazyv[idx]);
            apply(2*idx + 1, m + 1, e, lazyt[idx], lazyv[idx]);

            // reset lazy
            lazyt[idx] = lazytype::EMPTY;
            lazyv[idx] = 0;
        }
    }
    void update(int idx, int s, int e, int l, int r, lazytype t, ll val) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            apply(idx, s, e, t, val);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, t, val);
        update(2*idx + 1, m + 1, e, l, r, t, val);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    data query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return data{0};
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
    segtree tree(arr);
    int t, a, b, x;
    for (int i = 0; i < q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> a >> b >> x;
            a--, b--;
            
            tree.update(1, 0, n - 1, a, b, lazytype::INCR, x);
        } else if (t == 2) {
            cin >> a >> b >> x;
            a--, b--;

            tree.update(1, 0, n - 1, a, b, lazytype::SET, x);
        } else {
            cin >> a >> b;
            a--, b--;

            cout << tree.query(1, 0, n - 1, a, b).val << nline;
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