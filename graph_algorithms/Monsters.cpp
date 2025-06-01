/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1194/
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

#define N 1005
int n, m;
char grid[N][N];
pair<int,int> trace[N][N];
char tracedir[N][N];
vector<pair<int,int>> moves = {{1,0},{0,1},{-1,0},{0,-1}};
char dir[4] = {'D', 'R', 'U', 'L'}; 
vector<vector<int>> bfs(deque<pair<int,int>> &q) {
    vector<vector<int>> dist(n, vector<int>(m, IINF));
    for (int i = 0; i < (int) q.size(); i++) {
        dist[q[i].first][q[i].second] = 0;
    }
    while (q.size()) {
        for (int sz = q.size(); sz; sz--) {
            auto [i, j] = q.back();
            q.pop_back();
            for (auto move : moves) {
                int I = i + move.first;
                int J = j + move.second;
                if (0 <= I && I < n && 0 <= J && J < m && grid[I][J] != '#') {
                    if (dist[I][J] > dist[i][j] + 1) {
                        dist[I][J] = dist[i][j] + 1;
                        q.push_front({I, J});
                    }
                }
            }
        }
    }
    return move(dist);
}
void pre_compute() {
    
}
void solve() {
    cin >> n >> m;
    int xsrc = -1, ysrc = -1;
    deque<pair<int,int>> q1, q2, q3;
    for (int i = 0; i < n; i++ )
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'A') q1.push_front({i, j}), xsrc = i, ysrc = j;
            if (grid[i][j] == 'M') q2.push_front({i, j});
        }
    if (xsrc == 0 || xsrc == n - 1 || ysrc == 0 || ysrc == m - 1) {
        cout << "YES" << nline;
        return;
    }
    auto d1 = bfs(q1);
    auto d2 = bfs(q2);
    vector<vector<bool>> vis(n, vector<bool>(m));
    trace[xsrc][ysrc] = {-1,-1};
    q3.push_front({xsrc, ysrc});
    vis[xsrc][ysrc] = true;
    int xdst = -1, ydst = -1;
    while (q3.size() && xdst == -1) {
        for (int sz = q3.size(); sz; sz--) {
            auto [i, j] = q3.back();
            q3.pop_back();
            for (int k = 0; k < (int) moves.size();k++) {
                int I = i + moves[k].first;
                int J = j + moves[k].second;
                if (0 <= I && I < n && 0 <= J && J < m) {
                    if (d1[I][J] < d2[I][J] && !vis[I][J]) {
                        trace[I][J] = {i, j};
                        tracedir[I][J] = dir[k];
                        vis[I][J] = true;
                        q3.push_front({I, J});
                        if (I == 0 || I == n - 1 || J == 0 || J == m - 1) {
                            xdst = I, ydst = J;
                            break;
                        }
                    }
                }
            }
            if (xdst != -1) break;
        }
    }
    if (xdst == -1) {
        cout << "NO" << nline;
        return;
    }
    string path = "";
    while (xdst != xsrc || ydst != ysrc) {
        int next_x = trace[xdst][ydst].first;
        int next_y = trace[xdst][ydst].second;
        path += tracedir[xdst][ydst];
        xdst = next_x;
        ydst = next_y;
    }
    reverse(path.begin(), path.end());
    cout << "YES" << nline;
    cout << (int) path.size() << nline;
    cout << path << nline;
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