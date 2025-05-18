/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1667/
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
bool vis[N];
int trace[N];
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vis[1] = true;
    deque<int> q;
    q.push_front(1);
    int level = 0;
    bool found = false;
    trace[1] = -1;
    while (q.size()) {
        int sz = q.size();
        while (sz--) {
            int u = q.back();
            q.pop_back();
            if (u == n) {
                found = true;
                break;
            }
            for (auto v : g[u]) if (!vis[v]) {
                vis[v] = true;
                trace[v] = u;
                q.push_front(v);
            }
        }
        if (found) break;
        level++;
    }
    if (found) {
        int cur = n;
        vector<int> buf;
        while (cur != -1) {
            buf.push_back(cur);
            cur = trace[cur];
        }
        reverse(buf.begin(), buf.end());
        cout << buf.size() << nline;
        for (int i = 0; i < buf.size(); i++) {
            cout << buf[i] << ' ';
        }
    } else 
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