/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1655/
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

#define N 200005
#define BIT 30
int n, x[N];
struct Node {
    Node *child[2];  
};

void pre_compute() {
    
}
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i];

    Node *root = new Node{};
    {
        Node *p = root;
        for (int i = 0; i < BIT; i++) {
            p->child[0] = new Node{};
            p = p->child[0];
        }
    }
    int pxor = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, x[i]);
        pxor ^= x[i];
        int mask = 0;
        Node *p = root;
        for (int j = BIT - 1; j >= 0; j--) {
            int should = ((pxor >> j) & 1) ^ 1;
            if (p->child[should]) {
                mask ^= (should << j);
                p = p->child[should];
            } else {
                mask ^= ((!should) << j);
                p = p->child[!should];
            }
        }
        ans = max(ans, pxor ^ mask);
        p = root;
        int idx;
        for (int j = BIT - 1; j >= 0; j--) {
            idx = (pxor >> j) & 1;
            if (!p->child[idx]) p->child[idx] = new Node{};
            p = p->child[idx];
        }
    }
    cout << ans << nline;
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