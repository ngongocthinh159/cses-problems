/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1671/
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
int n, m;
vector<pair<int,int>> g[N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> q;
    q.push({0, 1});
    vector<ll> dist(n + 1, LINF);
    dist[1] = 0;
    while (q.size()) {
        auto [w_u, u] = q.top();
        q.pop();
        if (w_u > dist[u]) 
            continue;
        for (auto [v, w_uv] : g[u]) if (dist[v] > w_u + w_uv) {
            dist[v] = w_u + w_uv;
            q.push({dist[v], v});
        }
    }
    for (int i = 1; i <= n; i++) cout << dist[i] << ' ';
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