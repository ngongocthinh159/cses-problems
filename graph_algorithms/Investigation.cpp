/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1202/
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
int n, m;
vector<pair<int,ll>> g[N];
array<ll, 4> dp[N]; // <mn dist, mn dist route cnt, mn dist route mn flight, mn dist route mx flight>
bool vis[N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    fill(dp, dp + N, array<ll, 4>{LINF, 0, 0, 0});
    dp[1] = {0, 1, 0, 0};
    auto cmp = [] (auto &p1, auto &p2) {
        if (p2[0] < p1[0]) return true;
        return false;
    };
    priority_queue<array<ll, 2>,vector<array<ll, 2>>,decltype(cmp)> q(cmp);
    vis[1] = 1;
    q.push(array<ll, 2>{0, 1});
    while (q.size()) {
        auto [w_u, u] = q.top();
        q.pop();
        if (w_u > dp[u][0]) continue;
        auto [_, cntR, mnF, mxF] = dp[u];
        for (auto &[v, w_uv] : g[u]) {
            if (dp[v][0] > w_u + w_uv) {
                dp[v] = {w_u + w_uv, cntR, mnF + 1, mxF + 1};
                q.push({dp[v][0], v});
            } else if (dp[v][0] == w_u + w_uv) {
                int ncntR = cntR + dp[v][1];
                if (ncntR >= MOD) ncntR -= MOD;
                int nmnF = min(mnF + 1, dp[v][2]);
                int nmxF = max(mxF + 1, dp[v][3]);
                dp[v] = {w_u + w_uv, ncntR, nmnF, nmxF};
            }
        }
    }
    cout << dp[n][0] << " " << dp[n][1] << " " << dp[n][2] << " " << dp[n][3] << nline;
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
