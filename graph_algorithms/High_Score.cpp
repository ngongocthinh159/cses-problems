/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1673/
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

#define N 2505
#define AFFECT (-(LINF + 5))
int n, m;
vector<pair<int,int>> g[N];
struct Edge {
    int u, v, w;
    friend istream& operator >> (istream& is, Edge &e) {
        is >> e.u >> e.v >> e.w;
        return is;
    }
};
Edge edges[N*N];
bool maximize(ll &x, ll y) {
    if (x < y) {
        x = y;
        return true;
    }
    return false;
}
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> edges[i];
        g[edges[i].u].push_back({edges[i].v, edges[i].w});
    }
    vector<ll> dist(n + 1, -LINF);
    dist[1] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            Edge &e = edges[j];
            if (dist[e.u] != -LINF) maximize(dist[e.v], dist[e.u] + e.w);
        }
    }
    // mark vertices affected by the negative cycles
    deque<int> q;
    for (int j = 0; j < m; j++) {
        Edge &e = edges[j];
        if (dist[e.u] != -LINF && (dist[e.u] == AFFECT || maximize(dist[e.v], dist[e.u] + e.w))) {
            q.push_front(e.v);
            dist[e.v] = AFFECT;
        }
    }
    while (q.size()) {
        for (int sz = q.size(); sz; sz--) {
            int u = q.back();
            q.pop_back();
            dist[u] = AFFECT;
            for (auto [v, w] : g[u]) if (dist[v] != AFFECT) {
                dist[v] = AFFECT;
                q.push_front(v);
            }
        }
    }
    if (dist[n] == AFFECT)
        cout << -1 << nline;
    else
        cout << dist[n] << nline;
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
