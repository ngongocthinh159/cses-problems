/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1110/
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


void pre_compute() {
    
}
string shift_left(const string &s, int x) {
    string t = s;
    reverse(t.begin() + x, t.end());
    reverse(t.begin(), t.begin() + x);
    reverse(t.begin(), t.end());
    return t;
}
void solve() {
    int n;
    string s;
    cin >> s;
    n = s.size();
    bool same = true;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i - 1]) {
            same = false;
            break;
        }
    }
    if (same) {
        cout << s << nline;
        return;
    }
    n = s.size();
    string t = s;

    // Booth's algorithm
    // imagine we have two candidate rotations: i and j
    // find first length k where s[i + k] != s[j + k]
    // then suppose s[i + k] > s[j + k], then we can eliminate all rotations [i .. i + k], because
    // s[i] > s[j], s[i + 1] > s[j + 1],.. s[i + k] > s[j + k] all by the s[i + k] > s[j + k]
    // then we can increase i = i + k + 1 as the next candidate to compare to good candidate j
    // so every iteration we will eliminate a range of bad indices/rotations,
    // at max i can increase to n, and j can increase to n -> Time is O(2*n)

    // We need to handle special case, where i == j, then we should increase either i or j to have different candidates
    // Another special case where the whole string is the same character, then just return the whole string

    // To make our life easier when traverse i and j, just double the original string for rotation comparison
    s = s + s;
    int i = 0, j = 1;
    while (j < n) {
        int k = 0;
        while (s[i + k] == s[j + k]) k++;
        if (s[i + k] > s[j + k])
            i += k + 1;
        else
            j += k + 1;
        if (i == j) i++;
        if (i > j) swap(i, j);
    }
    cout << shift_left(t, i) << nline;
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