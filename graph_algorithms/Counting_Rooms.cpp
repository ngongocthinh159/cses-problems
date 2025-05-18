/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1192/
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
char mat[N][N];
bool vis[N][N];
void pre_compute() {
    
}
void dfs(int i , int j) {
    if (!(0 <= i && i < n && 0 <= j && j < m)) return;
    if (mat[i][j] == '#') return;
    if (vis[i][j]) return;
    vis[i][j] = true;
    dfs(i + 1, j);
    dfs(i - 1, j);
    dfs(i, j + 1);
    dfs(i, j - 1);
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> mat[i][j];
    int cnt = 0;
    for (int i = 0; i< n; i++)
        for (int j = 0; j < m; j++) if (!vis[i][j] && mat[i][j] == '.') {
            dfs(i, j);
            cnt++;
        }
    cout << cnt << nline;
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