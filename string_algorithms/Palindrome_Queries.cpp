/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/2420/
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

#define N 200005
int n, m;
string s;
const ll base = 32;
ll basepow[N], invbasepow[N];
struct segtree {
    vector<ll> nodes;
    vector<ll> lazy;
    int n;
    segtree(vector<ll> &arr) {
        n = arr.size();
        nodes.resize(4*n);
        lazy.resize(4*n);
        build(1, 0, n - 1, arr);
    }
    void build(int idx, int s, int e, vector<ll> &arr) {
        if (s == e) {
            nodes[idx] = arr[s];
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
    }
    void apply(int idx, int s, int e, ll delta) {
        nodes[idx] += delta;
        if (nodes[idx] >= MOD) nodes[idx] -= MOD;
        lazy[idx] += delta;
        if (lazy[idx] >= MOD) lazy[idx] -= MOD;
    }
    void push_down(int idx, int s, int e) {
        if (lazy[idx]) {
            int m = (s + e)/2;
            apply(2*idx, s, m, lazy[idx]);
            apply(2*idx + 1, m + 1, e, lazy[idx]);
            lazy[idx] = 0;
        }
    }
    void update(int idx, int s, int e, int l, int r, ll delta) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            apply(idx, s, e, delta);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, delta);
        update(2*idx + 1, m + 1, e, l, r, delta);
    }
    ll query(int idx, int s, int e, int pos) {
        if (s == e) return nodes[idx];
        push_down(idx, s, e);
        int m = (s + e)/2;
        if (pos <= m)
            return query(2*idx, s, m, pos);
        else
            return query(2*idx + 1, m + 1, e, pos);
    }
};
ll expo(ll a, ll b) {
    ll res = 1;
    ll cur = a;
    while (b) {
        if (b&1)
            res = res * cur % MOD;
        cur = cur * cur % MOD;
        b >>= 1;
    }
    return res;
}
void pre_compute() {
    basepow[0] = 1;
    for (int i= 1; i< N;i++) basepow[i] = basepow[i - 1] * base % MOD;
    invbasepow[N - 1] = expo(basepow[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) invbasepow[i] = invbasepow[i + 1] * base % MOD;
}
ll range_hash(int l, int r, segtree &tree) {
    ll res = tree.query(1, 0, n - 1, r);
    if (l - 1 >= 0) {
        res -= tree.query(1, 0, n - 1, l - 1);
        if (res < 0) res+=MOD;
    }
    res = res * invbasepow[l] % MOD;
    return res;
}
void solve() {
    cin >> n >> m >> s;
    vector<ll> pref(n), pref2(n);

    pref[0] = s[0] - 'a' + 1;
    for (int i = 1; i < n; i ++) {
        pref[i] = pref[i - 1] + (s[i] - 'a' + 1) * basepow[i] % MOD;
        if (pref[i] >= MOD) pref[i] -= MOD;
    }

    string t = s;
    reverse(all(t));
    pref2[0] = t[0] - 'a' + 1;
    for (int i = 1; i < n; i++) {
        pref2[i] = pref2[i - 1] + (t[i] - 'a' + 1) * basepow[i] % MOD;
        if (pref2[i] >= MOD) pref2[i] -= MOD;
    }

    segtree tree(pref);
    segtree tree2(pref2);

    int type, k, a, b;
    char x;
    for (int i = 0; i < m; i++) {
        cin >> type;
        if (type == 1) {
            cin >> k >> x;
            k--;
            
            ll delta = (-(s[k] - 'a' + 1) + (x - 'a' + 1));
            if (delta < 0) delta += MOD;
            delta = delta * basepow[k] % MOD;
            tree.update(1, 0, n - 1, k, n - 1, delta);

            ll delta2 = (-(t[n - 1 - k] - 'a' + 1) + (x - 'a' + 1));
            if (delta2 < 0) delta2 += MOD;
            delta2 = delta2 * basepow[n - 1 - k] % MOD;
            tree2.update(1, 0, n - 1, n - 1 - k, n - 1, delta2);

            s[k] = x;
            t[n - 1 - k] = x;
        } else {
            cin >> a >> b;
            a--, b--;

            int l = n - 1 - b, r = n - 1 - a;
            if (range_hash(a, b, tree) == range_hash(l, r, tree2)) 
                cout << "YES" << nline;
            else
                cout << "NO" << nline;
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