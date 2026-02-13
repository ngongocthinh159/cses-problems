/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/3405/
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

#define N 10000005
#define BIT 20
int n, k;
int x, a, b, c;
int arr[N], cnt[BIT];
void pre_compute() {
    
}
struct ds {
    vector<pair<int,int>> bot, top; // <x, aggregation>
    ds() {}
    void pop_front() {
        if (bot.size()) {
            bot.pop_back();
            return;
        }
        while (top.size()) {
            int x = top.back().first;
            int y = bot.size() ? bot.back().second : 0;
            bot.push_back({x, x | y});

            top.pop_back();
        }
        if (bot.size())
            bot.pop_back();
    }
    void push_back(int x) {
        int y = top.size() ? top.back().second : 0;
        top.push_back({x, x | y});
    }
    int value() {
        int x = top.size() ? top.back().second : 0;
        int y = bot.size() ? bot.back().second : 0;
        return x | y;
    }
};
void solve() {
    cin >> n >> k;
    cin >> x >> a >> b >> c;
    arr[0] = x;
    int ans = k == 1 ? arr[0] : 0;
    ds myds;
    myds.push_back(arr[0]);
    for (int i = 1; i < n; i++) {
        x = (1ll * x * a + b) % c; 
        arr[i] = x;
        if (i - k >= 0) myds.pop_front();
        myds.push_back(arr[i]);
        if (i >= k - 1) 
            ans ^= myds.value();
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