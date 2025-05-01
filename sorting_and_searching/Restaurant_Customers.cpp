/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1619/
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


void pre_compute() {
    
}
void solve() {
    int n;
    struct Event {
        int time, type;
    };
    cin >> n;
    Event events[400010];
    for (int i = 0; i < n ;i++) {
        int s, e; cin >> s >> e;
        events[2*i].time = s;
        events[2*i].type = 1;
        events[2*i + 1].time = e;
        events[2*i + 1].type = -1;
    }
    sort(events, events + 2*n, [&](Event &e1, Event &e2) {
        if (e1.time < e2.time) return true;
        if (e1.time == e2.time && e1.type == 1 && e2.type == 0) return true;
        return false;
    });
    int cnt = 0, ans = 0;
    for (int i = 0; i < 2*n; i++) {
        cnt += events[i].type;
        ans = max(ans, cnt);
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