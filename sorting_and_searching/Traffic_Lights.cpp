/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1163/
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


void pre_compute() {
    
}
void solve() {
    int L, n;
    cin >> L >> n;
    set<int> pos;
    pos.insert(0), pos.insert(L);
    multiset<int> segments;
    segments.insert(L);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;

        auto it = pos.lower_bound(x);
        int r = *it;
        it--;
        int l = *it;
        
        segments.erase(segments.find(r - l));
        segments.insert(x - l);
        segments.insert(r - x);
        pos.insert(x);

        cout << *segments.rbegin() << nline;
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
