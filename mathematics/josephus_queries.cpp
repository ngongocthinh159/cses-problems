#include <bits/stdc++.h>
using namespace std;

/* clang-format off */

/* TYPES  */
#define ll long long

/* clang-format on */
void solve();
ll f(ll n, ll k) {
    if(n==1) return 1;
    if(k<=(n+1)/2) {
        if(2*k>n) return 2*k-n;
        else return 2*k;
    }
    ll temp=f(n/2,k-(n+1)/2);
    if(n%2==1) return 2*temp+1;
    return 2*temp-1;
}

/* Main()  function */
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    ll cases;
    cin >> cases;

    while (cases--) {
        solve();
    }

    // ll q;
    // cin>>q;
    // for(int i=0;i<q;i++) {
    //     ll n,k;
    //     cin>>n>>k;
    //     cout<<f(n,k)<<"\n";
    // }
}

void solve() {
    ll n, k;
    cin >> n >> k;

    if (k <= n/2) {cout << (2*k) << "\n"; return;}

    ll startNum = -1, delFrom = -1, loop = 1;
    if (n%2 == 0) { // Even, delete from 2
        startNum = 1;
        delFrom = 2;
    } else { // Odd, delete from 2
        startNum = 1;
        delFrom = 1;
    }

    k -= n/2;
    n -= n/2;
    while (true) {
        ll willRemove;
        if (n%2==0) willRemove = n/2;
        else {
            if (delFrom == 1) willRemove = (n + 1) / 2;
            else if (delFrom == 2) willRemove = n/2;
        }

        if (k - willRemove <= 0) {
            if (delFrom == 1) {
                ll tmp = startNum + pow(2,loop + 1)*(k - 1);
                cout << tmp << "\n";
            }
            else if (delFrom == 2) {
                ll tmp = startNum + pow(2,loop) + pow(2,loop + 1)*(k - 1);
                cout << tmp << "\n";
            }
            return;
        } else if (willRemove == 0) {
            cout << startNum << "\n";
            return;
        }

        if (n % 2 == 0) {
            if (delFrom == 2) {
                startNum = startNum; delFrom = 2;
            } else if (delFrom == 1) {
                startNum += pow(2, loop); delFrom = 1;
            }
        } else {
            if (delFrom == 2) {
                startNum = startNum; delFrom = 1;
            } else if (delFrom == 1) {
                startNum += pow(2, loop); delFrom = 2;
            }
        }

        k -= willRemove;
        n -= willRemove;
        loop++;
    }
}

/* Main() Ends Here */