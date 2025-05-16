/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1642/
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

// reference: https://usaco.guide/problems/cses-1642-sum-of-four-values/solution
void pre_compute() {
    
}
void solve() {
    int n, x; cin >> n >> x;
    int a[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    unordered_map<int,pair<int,int>> freq;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            int target = x - a[i] - a[j];
            if (freq.count(target)) {
                cout << j + 1 << ' ' << i + 1 << ' ' << freq[target].first + 1 << ' ' << freq[target].second + 1 << nline; 
                return;
            }
        }
        for (int j = i + 1; j < n; j++) freq[a[i] + a[j]] = {j, i};
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