/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1112/
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

#define N 1005
#define M 105
#define next __next
int n, m;
string s;
ll dp[N][M];
int next[M][26];
void pre_compute() {
    
}
void build_automata() {
    vector<int> kmp(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (j != 0 && s[i] != s[j]) j = kmp[j - 1];
        kmp[i] = s[i] == s[j] ? ++j : 0;
    }

    next[0][s[0] - 'A'] = 1;
    for (int i = 1; i < m; i++)
        for (int c = 0; c < 26; c++) {
            if (c == s[i] - 'A') 
                next[i][c] = i + 1;
            else
                next[i][c] = next[kmp[i - 1]][c];
        }
}
void solve() {
    cin >> n >> s;
    m = s.size();

    build_automata();

    dp[0][0] = 1;
    ll res = 1;
    for (int i = 0; i < n; i++) {
        res = res * 26 % MOD;
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < 26; c++) {
                int matched = next[j][c];
                if (matched == m) continue;
                dp[i + 1][matched] += dp[i][j];
                if (dp[i + 1][matched] >= MOD) dp[i + 1][matched] -= MOD;
            }
        }
    }
    for (int j = 0; j < m; j++) {
        res -= dp[n][j];
        if (res < 0) res += MOD;
    }
    cout << res << nline;
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