/**
 * Author: Thinh Ngo Ngoc
 * Solution for: 
*/

#include<bits/stdc++.h>
using namespace std;

#define nline '\n'
#define ll long long
#define MOD 1000000007
#define MOD1 998244353
#define LINF ((long long)1e18)
#define IINF ((int)1e9)

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 100005
int n, m, k;
vector<pair<int,int>> g[N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> m >> k;
    for (int i = 0; i <m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    vector<int> cnt(n+1, k);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> q;
    vector<priority_queue<ll>> distNode(n + 1);
    distNode[1].push(0);
    q.push({0, 1});
    vector<ll> ans;
    // https://usaco.guide/problems/cses-1196-flight-routes/solution
    // https://en.wikipedia.org/wiki/K_shortest_path_routing
    while (q.size()) {  
        auto [w_u, u] = q.top();
        q.pop();
        if (!cnt[u]) continue;
        cnt[u]--;
        if (u == n) ans.push_back(w_u);
        for (auto [v, w_uv] : g[u]) {
            if ((int) distNode[v].size() < k) {
                distNode[v].push(w_u + w_uv);
                q.push({w_u + w_uv, v});
            } else if (w_u + w_uv < distNode[v].top()) {
                distNode[v].pop();
                distNode[v].push(w_u + w_uv);
                q.push({w_u + w_uv, v});
            }
        }
    }
    for (auto x : ans) cout << x << ' ';
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