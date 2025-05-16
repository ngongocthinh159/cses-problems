/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/2162/
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

#define next __next
struct Node {
    int val;
    Node* next;
};
void pre_compute() {
    
}
Node* get_next(Node* p, Node* head) {
    if (p->next) 
        return p->next;
    else 
        return head->next;
}
void solve() {
    int n;
    cin >> n;
    Node* head = new Node;
    Node* p = head;
    for (int i = 1; i <= n; i++) {
        Node* new_node = new Node;
        new_node->val = i;
        p->next = new_node;
        p = p->next;
    }
    Node* prev;
    p = head;
    for (int i = 1; i <= n; i++) {
        p = get_next(p, head);
        prev = p;
        p = get_next(p, head);

        cout << p->val << ' ';
        prev->next = get_next(p, head);
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