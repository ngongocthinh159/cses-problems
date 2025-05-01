/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/result/12769143/
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
struct custom_hash {static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}}; // https://codeforces.com/blog/entry/62393

/*--------------------------------------------------------------------------------------------------------------------------*/

#define N 200005
int num_to_idx[N], num[N];
void pre_compute() {
    
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        num_to_idx[x] = i;
        num[i] = x;
    }
    int prev = -1, chain = 1;
    for (int i = 1; i <= n; i++) {
        if (num_to_idx[i] < prev) {
            chain++;
        }
        prev = num_to_idx[i];
    }
    num_to_idx[n + 1] = n;
    vector<int> buf, old_idx;
    for (int k = 0; k < m; k++) {
        int idx_a, idx_b; cin >> idx_a >> idx_b;
        idx_a--; idx_b--;
        int a = num[idx_a], b = num[idx_b];
        
        buf.clear();
        old_idx.clear();
        buf.push_back(a);
        buf.push_back(a - 1);
        buf.push_back(a + 1);
        buf.push_back(b);
        buf.push_back(b - 1);
        buf.push_back(b + 1);
        sort(buf.begin(), buf.end());
        buf.erase(unique(buf.begin(), buf.end()), buf.end());
        
        old_idx.resize(buf.size());
        for (int i = 0; i < buf.size(); i++) old_idx[i] = num_to_idx[buf[i]];

        num[idx_a] = b;
        num[idx_b] = a;
        num_to_idx[a] = idx_b;
        num_to_idx[b] = idx_a;

        for (int i = 1; i < buf.size(); i++) {
            if (buf[i] - buf[i - 1] == 1) { // update chain count based on number of inversion pairs of consecutive elements
                if (old_idx[i - 1] > old_idx[i] && num_to_idx[buf[i - 1]] < num_to_idx[buf[i]]) chain--;
                if (old_idx[i - 1] < old_idx[i] && num_to_idx[buf[i - 1]] > num_to_idx[buf[i]]) chain++;
            }
        }

        cout << chain << nline;
    }
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


