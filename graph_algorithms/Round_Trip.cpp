/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1669/
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
vector<int> g[N];
int color[N], trace[N];
void pre_compute() {
    
}
void dfs(int u, int p, int &ver_e, int &ver_s) {
    color[u] = 1;
    for (auto v : g[u]) if (v != p) {
        if (color[v] == 1) {
            ver_e = u;
            ver_s = v;
        } else if (color[v] == 0) {
            trace[v] = u;
            dfs(v, u, ver_e, ver_s);
        }
    }
    color[u] = 2;
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) if (color[i] == 0) {
        int ver_e = -1, ver_s;
        dfs(i, -1, ver_e, ver_s);
        if (ver_e != -1) {
            vector<int> buf;
            buf.push_back(ver_s);
            while (ver_e != ver_s) {
                buf.push_back(ver_e);
                ver_e = trace[ver_e];
            }
            buf.push_back(ver_s);
            reverse(buf.begin(), buf.end());
            cout << buf.size() << nline;
            for (auto u : buf) cout << u << ' ';
            return;
        }
    }
    cout << "IMPOSSIBLE" << nline;
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