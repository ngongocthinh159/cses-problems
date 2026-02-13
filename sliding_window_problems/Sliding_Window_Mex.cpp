/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/3219/
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
#define LOG 30
int n, k;
int a[N];
int _2pow[LOG];
unordered_map<int,int> f;
struct node {
    node *child[2];
    ll cnt;
    node() {
        child[0] = child[1] = nullptr;
        cnt = 0;
    }
};

void pre_compute() {
    _2pow[0] = 1;
    for (int i = 1; i < LOG; i++) _2pow[i] = _2pow[i - 1] * 2;
}
void insert(node *root, int x) {
    node *p = root;

    int delta = (++f[x] == 1 ? 1 : 0);
    p->cnt += delta;
    int idx;
    for (int bit = LOG - 1; bit >= 0; bit--) {
        idx = (x >> bit) & 1;
        if (!p->child[idx]) p->child[idx] = new node;
        p = p->child[idx];
        p->cnt += delta;
    }
}
void remove(node *root, int x) {
    node *p = root;

    int delta = (--f[x] == 0 ? -1 : 0);
    p->cnt += delta;
    int idx;
    for (int bit = LOG - 1; bit >= 0; bit--) {
        idx = (x >> bit) & 1;
        p = p->child[idx];
        p->cnt += delta;
    }
}
int find_mex(node *root) {
    node *p = root;
    int res = 0;
    for (int bit = LOG - 1; bit >= 0; bit--) {
        int cntl = p->child[0] == nullptr ? 0 : p->child[0]->cnt;
        int desired = _2pow[bit];
        if (cntl == desired) {
            res = res ^ (1 << bit);
            if (!p->child[1]) return res;
            p = p->child[1];
        } else {
            if (!p->child[0]) return res;
            p = p->child[0];
        }
    }
    return res;
}
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];

    node *root = new node;
    
    f.reserve(2e6);
    for (int i = 0; i < k; i++) insert(root, a[i]);
    cout << find_mex(root) << ' ';
    for (int i = k; i < n; i++) {
        remove(root, a[i - k]);
        insert(root, a[i]);
        cout << find_mex(root) << ' ';
    }
    cout << nline;
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