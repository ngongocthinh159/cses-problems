/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1731/
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
struct node {
    node *child[26];
    int cnt;
    node() {
        for (int i = 0; i < 26; i++) child[i] = nullptr;
        cnt = 0;
    }
};
#define N 5005
int n, k;
vector<string> words;
string s;
void pre_compute() {
    
}
void insert(node *root, const string &t) {
    node *p = root;
    int idx;
    for (auto c : t) {
        idx = c - 'a';
        if (!p->child[idx]) p->child[idx] = new node;
        p = p->child[idx];
    }
    p->cnt++;
}
void solve() {
    cin >> s;
    n = s.size();
    cin >> k;
    words.resize(k);
    node *root = new node;
    for (int i=0; i < k;i++) 
        cin >> words[i], insert(root, words[i]);
    vector<ll> dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        node *p = root;
        int idx;
        for (int j = i; j < n; j++) {
            idx = s[j] - 'a';
            if (!p->child[idx]) break;
            p = p->child[idx];
            if (p->cnt != 0) {
                dp[i] += dp[j + 1];
                if (dp[i] >= MOD) dp[i] -= MOD;
            }
        }
    }
    cout << dp[0] << nline;
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