/**
 * Author: Thinh Ngo Ngoc
 * Solution for: https://cses.fi/problemset/task/1732/
*/
#pragma GCC optimize("O3,unroll-loops")
 
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace chrono;
using namespace __gnu_pbds;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
void IN_OUT() {
#ifndef ONLINE_JUDGE
freopen("Input.txt", "r", stdin);
freopen("Output.txt", "w", stdout);
#endif
}
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits(x) __builtin_popcountll(x)
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

// #define ThinhNgo
#ifdef ThinhNgo
#define debug(x) cerr << #x<<" "; _print(x); cerr << endl;
#else
#define debug(x);
#endif
 
using ll = long long;
using ull = unsigned long long;
using lld = long double;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
 
void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}
 
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
void _print(pbds v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/*---------------------------------------------------------------------------------------------------------------------------*/
ll __gcd__(ll a, ll b) {if (!a || !b) return a | b; unsigned shift = __builtin_ctz(a | b); a >>= __builtin_ctz(a); do { b >>= __builtin_ctz(b); if (a > b) swap(a, b); b -= a; } while (b); return a << shift;} // only a >= 0 && b >= 0
ll gcd(ll a, ll b) {a = abs(a); b = abs(b); return __gcd__(a, b);} // get abs(a), abs(b) in case a < 0 || b < 0
ll expo(ll a, ll b, ll mod) {if (a==0) return 1%mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
ll expo(ll a, ll b) {ll res = 1; while (b > 0) {if (b & 1)res = res * a; a = a * a; b = b >> 1;} return res;} // a = 0 return 0 | b = 0 return 1
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {assert(gcd(a, b) == 1); return expo(a, b - 2, b);} // inverse mod: a^-1 % b = a^(b-2) % b. When gcd(a,b)=1 (or b prime)
bool revsort(ll a, ll b) {return a > b;}
ll combination(ll n, ll r, ll m, ll *fact, ll *ifact) {ll val1 = fact[n]; ll val2 = ifact[n - r]; ll val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
void google(int t) {cout << "Case #" << t << ": ";}
vector<ll> sieve(int n) {int*arr = new int[n + 1](); vector<ll> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0) n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
ll getRandomNumber(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
/*--------------------------------------------------------------------------------------------------------------------------*/
// #define ThinhNgo_use_cases

void pre_compute() {

}

// "Must" Adjust default global mxn ONE (max base pow need: normally max(string.size()) + 1): the default_globalMxn must be the same for every string, do not change it for each string processing (the first adjust must be largest)
// Adjust should random base for every compile or use default global base is 31
// Adjust list of random bases: each base > largest unique mapped values. Base can not be prime
// Adjust list of mods: each mod must be prime and should ~= 10^9 (normally two primes is ok, if collision use three primes)
// Adjust mapped values in map_to_ll function: each different char or int must be mapped into a unique ll
ll default_globalMxn = 1e6 + 5;
bool randomBase = true;
vector<int> random_bases = {31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89};
ll globalBase = 31;
const vector<ll> primes = {1000000009, 1000000007};

ll globalMxN = default_globalMxn;
vector<vector<ll>> base_pow;
vector<vector<ll>> i_base_pow;
bool isRandomBaseGenerated = false;
bool isBasePowPrecomputed = false;
int gen_base() {
    int randomIdx = getRandomNumber(0, (int) random_bases.size() - 1);
    return random_bases[randomIdx];
}
void pre_compute_base_pow() {
    isBasePowPrecomputed = true;

    int prime_count = primes.size();
    base_pow = vector<vector<ll>>(prime_count, vector<ll>(globalMxN + 1));
    i_base_pow = vector<vector<ll>>(prime_count, vector<ll>(globalMxN + 1));

    for (int j = 0; j < primes.size(); j++) {
        base_pow[j][0] = 1;
        for (int i = 1; i <= globalMxN; i++) {
            base_pow[j][i] = (base_pow[j][i - 1] * globalBase) % primes[j]; 
        }
        
        i_base_pow[j][0] = 1;
        i_base_pow[j][1] = expo(globalBase, primes[j] - 2, primes[j]);
        for (int i = 2; i <= globalMxN; i++) {
            i_base_pow[j][i] = (i_base_pow[j][i - 1] * i_base_pow[j][1]) % primes[j];
        }
    }
}
struct SH {
    ll n;
    string s;
    vector<vector<ll>> prefix_hash;
    
    SH(string queryString) {
        assert(primes.size() > 0);
        assert(queryString.size() > 0);
        assert((int) s.size() <= globalMxN);
        assert(globalMxN == default_globalMxn);

        if (randomBase && !isRandomBaseGenerated) {
            globalBase = gen_base();
            isRandomBaseGenerated = true;
        }

        if (!isBasePowPrecomputed) {
            pre_compute_base_pow();
            isBasePowPrecomputed = true;
        }

        // Generate prefix hash for current SH        
        s = queryString;
        n = s.size();
        pre_compute_prefix_hash();
    }

    void pre_compute_prefix_hash() {
        ll prime_count = primes.size();
        prefix_hash = vector<vector<ll>>(prime_count, vector<ll>(n + 1));

        for (int j = 0; j < primes.size(); j++) {
            for (int i = 1; i <= n; i++) {
                ll mapped_number = map_to_ll(s[i - 1]);
                prefix_hash[j][i] = (prefix_hash[j][i - 1] + ((mapped_number*base_pow[j][i - 1]) % primes[j])) % primes[j];
            }
        }
    }

    // Mapping from a character of S to a number
    // Each unique character must be mapped into a unique number (same for array of integers)
    // The smallest mapped number should be 1 (not 0)
    ll map_to_ll(char &c) {
        return (c - 'a' + 1);
    }

    // O(1)
    // Base 0: Calculate hash of a range
    vector<ll> hash_in_range(ll l, ll r) {
        vector<ll> res;
        for (int i = 0; i < primes.size(); i++) {
            ll tmp = (prefix_hash[i][r + 1] - prefix_hash[i][l]) % primes[i];
            if (tmp < 0) tmp = (tmp + primes[i]) % primes[i];
            tmp = (tmp * i_base_pow[i][l]) % primes[i];
            res.push_back(tmp);
        }
        return res;
    }
};
// O(1)
// sh2 must be a SH object of the reversed string
bool is_palindrome(ll l, ll r, SH &sh1, SH &sh2) {
    ll size = sh1.s.size();
    ll l2 = size - (r + 1);
    ll r2 = size - (l + 1);
    return sh1.hash_in_range(l, r) == sh2.hash_in_range(l2, r2);
}


string s;
void solve() {
    cin >> s;
    SH hash(s);
    int n = s.size();
    vector<int> res;
    for (int len = 1; len < n; len++) {
        if (hash.hash_in_range(0, len - 1) == hash.hash_in_range(n - len, n - 1)) res.push_back(len);
    }
    for (auto x : res) {
        cout << x << " ";
    }
}

int main() {
#ifdef ThinhNgo
    freopen("Error.txt", "w", stderr);
#endif
    fastio();
    IN_OUT();
    auto start1 = high_resolution_clock::now();
    int T = 1;
#ifdef ThinhNgo_use_cases
    cin >> T;
#endif
    pre_compute();
    while (T--) {
        solve();
    }
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
#ifdef ThinhNgo
    cerr << "Time: " << duration . count() / 1000 << " ms" << endl;
#endif
}
