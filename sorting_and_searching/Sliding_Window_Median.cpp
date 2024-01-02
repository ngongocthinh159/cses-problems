/**
 * Solution for: https://cses.fi/problemset/task/1076/
*/

#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

const int N = 2e5 + 5;
int n, k;
int a[N];
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int idx = (k-1)/2;
    pbds st;
    vector<int> ans;
    for (int r = 0; r < k; r++) {
        st.insert({a[r], r});
    }
    ans.push_back((*st.find_by_order(idx)).first);
    for (int r = k; r < n; r++) {
        st.erase({a[r - k], r - k});
        st.insert({a[r], r});
        ans.push_back((*st.find_by_order(idx)).first);
    }
    for (auto num : ans) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    solve();
    return 0;
}