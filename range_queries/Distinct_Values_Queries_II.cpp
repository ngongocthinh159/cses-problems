/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/3356/
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
#define data __data
int n, q;
int a[N];
struct data {
    ll mn;
};
struct segtree {
    vector<data> nodes;
    int n;
    segtree(vector<int> &arr) {
        n = arr.size();
        nodes.resize(4*n);
        build(1, 0, n - 1, arr);
    }
    data merge(data &l, data &r) {
        data res;
        res.mn = min(l.mn, r.mn);
        return res;
    }
    void build(int idx, int s, int e, vector<int> &arr) {
        if (s == e) {
            nodes[idx].mn = arr[s];
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    void update(int idx, int s, int e, int pos, int  val) {
        if (s == e) {
            nodes[idx].mn = val;
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, val);
        else
            update(2*idx + 1, m + 1, e, pos, val);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return IINF;
        if (l <= s && e <= r) return nodes[idx].mn;
        int m = (s + e)/2;
        int lans = query(2*idx, s, m, l, r);
        int rans = query(2*idx + 1, m + 1, e, l, r);
        return min(lans, rans);
    }  
};

// always maintain the array: next[i] mean the index of the next element a[i] in the array
// a range [l, r] is all distinct if min(next[l..r]) > r

void pre_compute() {
    
}
void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> arr(n);
    unordered_map<int,int> nxt;
    unordered_map<int,set<int>> f;
    nxt.reserve(1e6);
    f.reserve(1e6);
    for (int i = n - 1; i >= 0; i--) {
        int j; 
        if (!nxt.count(a[i])) j = IINF;
        else j = nxt[a[i]];
        nxt[a[i]] = i;

        f[a[i]].insert(i);
        arr[i] = j;
    }
    segtree tree(arr);

    auto find = [](int idx, const set<int> &S) -> pair<int,int> {
        auto it = S.upper_bound(idx);
        int l, r;
        if (it == S.end()) r = IINF;
        else r = *it;
        if (it == S.begin()) l = -1;
        else {
            it--;
            l = *it;
        }
        return {l, r};
    };
    int t, idx, u, l, r;
    for (int i = 0; i < q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> idx >> u;
            idx--;

            f[a[idx]].erase(idx);

            auto [lidx1, ridx1] = find(idx, f[a[idx]]);
            if (lidx1 != -1)
                tree.update(1, 0, n - 1, lidx1, ridx1);

            auto [lidx2, ridx2] = find(idx, f[u]);
            
            if (lidx2 != -1)
                tree.update(1, 0, n - 1, lidx2, idx);
            tree.update(1, 0, n - 1, idx, ridx2);

            f[u].insert(idx);

            a[idx] = u;
        } else {
            cin >> l >> r;
            l--, r--;

            if (tree.query(1, 0, n - 1, l, r) > r) 
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