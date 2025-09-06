/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1741/
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

#define N 100005
#define x1 _x1
#define x2 _x2
#define y1 _y1
#define y2 _y2

struct Event {
    int x; 
    int type;
    int y1;
    int y2;
};
int n, y[2*N];
int top1, top, topE;
unordered_map<int,int,chash> yToIdx;
Event es[2*N];
struct Data {
    int mn = 0;
    int len = 0;
    int lazy = 0;
    // Data() {
    //     mn = 0, len = 0, lazy = 0;
    // }
};
struct SegTree {
    vector<Data> node;
    vector<int> lazy;
    int n;
    SegTree(int _n) {
        n = _n;
        node.assign(4*n, Data{0, 0, 0});

        node.resize(4*n);
        lazy.resize(4*n);
        build(1, 0, n - 1);
    }
    Data merge(const Data &l, const Data &r) {
        Data res;
        if (l.mn < r.mn) {
            res = l;
        } else if (l.mn > r.mn) {
            res = r;
        } else {
            res.mn = l.mn;
            res.len = l.len + r.len;
        }
        res.lazy = 0; // IMPORTANT: parent node will not inherit lazy value from children when merge, this is subtle bug
        return res;
    }
    void build(int idx, int s, int e) {
        if (s == e) {
            node[idx].mn = 0;
            node[idx].len = y[s + 1] - y[s];
            node[idx].lazy = 0;
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m);
        build(2*idx + 1, m + 1, e);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    void apply(int idx, int s, int e, int val) {
        node[idx].mn += val;
        node[idx].lazy += val;
    }
    void push_down(int idx, int s, int e) {
        int m = (s + e)/2;
        apply(2*idx, s, m, node[idx].lazy);
        apply(2*idx + 1, m + 1, e, node[idx].lazy);
        node[idx].lazy = 0;
    }
    void update(int idx, int s, int e, int l, int r, int val) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            apply(idx, s, e, val);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, val);
        update(2*idx + 1, m + 1, e, l, r, val);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    int covered_len() {
        if (n == 0) return 0;
        ll res = y[top - 1] - y[0];
        if (node[1].mn == 0) res -= node[1].len;
        return res;
    }
};

void pre_compute() {
    
}
void solve() {
    cin >> n;
    top = 0, topE = 0;
    for (int i = 0; i < n; i++) {
        
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        int l = min(x1, x2);
        int r = max(x1, x2);
        int t = max(y1, y2);
        int b = min(y1, y2);

        y[top++] = y1;
        y[top++] = y2;
        es[topE++] = Event{l, 1, b, t};
        es[topE++] = Event{r, -1, b, t};
    }
    sort(es, es + topE, [&](auto &e1, auto &e2) {
        if (e1.x < e2.x) return true;
        return false;
    });
    sort(y, y + top);
    top = unique(y, y + top) - y;
    for (int i = 0; i < top; i++)
        yToIdx[y[i]] = yToIdx.size();
    int interval = top - 1;
    SegTree tree(interval);
    int px = es[0].x;
    ll ans = 0;
    for (int i = 0; i < topE;) {
        ans += 1LL * (es[i].x - px) * tree.covered_len();
        
        int sx = es[i].x;
        px = es[i].x;
        while (i < topE && sx == es[i].x) {
            tree.update(1, 0, interval - 1, yToIdx[es[i].y1], yToIdx[es[i].y2] - 1, es[i].type);
            i++;
        }
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