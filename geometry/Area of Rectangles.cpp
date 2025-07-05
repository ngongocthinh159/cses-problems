/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1741
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
#define M 400005
struct Event {
    int x, y1, y2, delta;
};
int n;
int y[N];
Event events[M];
struct SegTree {
    struct Data {
        int cnt;
        ll sum;
    };
    vector<Data> node;
    int n;
    SegTree(int sz) {
        n = sz;
        node.resize(4*n);
    }
    void update(int idx, int s, int e, int l, int r, int delta) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            node[idx].cnt += delta;
        } else {
            int m = (s + e)/2;
            update(2*idx, s, m, l, r, delta);
            update(2*idx + 1, m + 1, e, l, r, delta);
        }
        // merge
        if (node[idx].cnt > 0)
            node[idx].sum = y[e + 1] - y[s];
        else {
            if (s == e)
                node[idx].sum = 0;
            else
                node[idx].sum = node[2*idx].sum + node[2*idx + 1].sum;
        }
    }
    ll coveredSum() {
        return node[1].sum;
    }
};
void pre_compute() {
    
}
void solve() {
    cin >> n;
    int top = 0;
    int topE = 0;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        int l = min(x1, x2);
        int r = max(x1, x2);
        int t = max(y1, y2);
        int b = min(y1, y2);
        y[top++] = y1;
        y[top++] = y2;
        events[topE++] = Event{l, b, t, 1};
        events[topE++] = Event{r, b, t, -1};
    }
    sort(y, y + top);
    top = unique(y, y + top) - y;
    sort(events, events + topE, [](auto &e1, auto &e2) {
        return e1.x < e2.x;
    });
    unordered_map<int,int,chash> yToIdx;
    for (int i = 0; i < top; i++) yToIdx[y[i]] = yToIdx.size();
    int segments = top - 1;
    SegTree tree(segments);
    ll ans = 0;
    int prev_x = 0;
    for (int i = 0; i < topE; i++) {
        ans += 1LL * (events[i].x - prev_x) * tree.coveredSum();
        prev_x = events[i].x;
        tree.update(1, 0, segments - 1, yToIdx[events[i].y1], yToIdx[events[i].y2] - 1, events[i].delta);
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