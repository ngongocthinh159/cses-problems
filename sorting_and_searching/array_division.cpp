/*
    Solution for: https://cses.fi/problemset/task/1085
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 2*1e5 + 5;
int n, k;
int nums[N];
bool check(long long m, int k) {
    int cnt = 1;
    long long sum = 0;
    int r = 0;
    while (r < n) {
        if (nums[r] > m) return false;
        sum += nums[r];

        if (sum > m) {
            sum = nums[r];
            cnt++;
            if (cnt > k) return false;
        }

        r++;
    }
    return true;
}
 
void solve() {
    cin >> n >> k;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += (long long) nums[i];
    }
    long long l = 0, r = sum;
    long long ans = LONG_MIN;
    while (l <= r) {
        long long m = l + (r - l)/2;

        if (check(m, k)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    solve();    
    return 0;
}