#include <bits/stdc++.h>
#define yes    printf("Yes\n")
#define no     printf("No\n")
#define ll     long long
#define all(x) x.begin(), x.end()
#define fastIO                   \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0)
using namespace std;

int       is_prime[1000001];
const int N   = 1e6;
const int mod = 998244353;

ll ksm(ll a, ll n, ll mod)
{
    ll ans = 1;
    ll c   = a % mod;
    while (n >= 1) {
        if (n & 1) {
            ans *= c;
            ans %= mod;
        }
        c = c * c;
        c %= mod;
        n /= 2;
    }
    return ans;
}

ll inv(ll a, ll mod)
{
    return ksm(a, mod - 2, mod);
}

int main()
{
    // precalc : prime
    for (int i = 2; i <= N; i++)
        is_prime[i] = 1;
    for (int i = 2; i <= N; i++) {
        if (!is_prime[i]) continue;
        for (int j = 2 * i; j <= N; j += i) {
            is_prime[j] = 0;
        }
    }

    // precal for fen kuai
    // pre_product for primes
    vector<ll> premul(N + 1);
    premul[0] = 1;
    premul[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (is_prime[i])
            premul[i] = premul[i - 1] * i;
        else
            premul[i] = premul[i - 1];
        premul[i] %= mod;
    }

    int testcases;
    cin >> testcases;  // REMEMBER THE Initialization !
    while (testcases--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        ll k = 0, ans = 1;
        for (int i = 0; i < s.size(); i++) {
            k *= 10;
            k += s[i] - '0';
            // phi(mod-1) = phi(998244353-1) = 402653184
            k %= 402653184;
        }

        //        //Time Complexity : O(n) but correct.
        //        for(int i=2;i<=n;i++){
        //        Try fen kuai
        
        for (int i = 2; i <= sqrt(n); i++) {
            if (!is_prime[i]) continue;
            ll base = i;
            while (base <= n) {
                ll cnt = ksm(n - n / base / i, k, mod - 1) - ksm(n - n / base, k, mod - 1);
                cnt    = (cnt % (mod - 1) + mod - 1) % (mod - 1);
                ans *= ksm(base, cnt, mod);
                ans %= mod;
                base *= (ll)i;
            }
        }

        for (int j = 1; j < sqrt(n); j++) {
            // for n/[base] = j
            int l = n / (j + 1) + 1, r = n / j;

            if (l < sqrt(n)) l = sqrt(n);
            if (r <= sqrt(n)) break;

            // cerr << "dbg " << n << " " << j << " " << l << " " << r << "\n";
            ll cnt = ksm(n, k, mod - 1) - ksm(n - j, k, mod - 1);
            cnt    = (cnt % (mod - 1) + mod - 1) % (mod - 1);
            ans *= ksm(premul[r] * inv(premul[l - 1], mod) % mod, cnt, mod);
            ans %= mod;
        }

        cout << ans << "\n";
    }
    return 0;
}