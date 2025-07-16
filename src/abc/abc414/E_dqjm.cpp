#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll   long long

const int mod = 998244353;

ll f(ll a, ll b, ll c)
{
    if (b == 0) return 1 % c;
    ll v = f(a * a % c, b / 2, c);
    if (b % 2) v = v * a % c;
    return v;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n;
    cin >> n;
    ll sum = ((n - 2ll) % mod * (n % mod) % mod + n - 2) % mod
             - (n + 1) % mod * ((n - 2) % mod) % mod * f(2, mod - 2, mod) % mod;
    sum %= mod;
    sum += mod;
    sum %= mod;
    if (n <= 1e6) {
        for (int i = 2; i <= n - 1; i++) {
            sum -= n / i;
            sum %= mod;
            sum += mod;
            sum %= mod;
        }
    } else {
        for (int i = 2; i <= 1e6; i++) {
            sum -= n / i;
            sum %= mod;
            sum += mod;
            sum %= mod;
        }
        for (int i = 1; i <= 1e6; i++) {
            ll l = ((n + 1 + i - 1) / i) - 1, r = n / i;
            if (r <= 1e6) continue;
            l = max((ll)(1e6 + 1), l);
            r = min(n - 1, r);
            sum -= (r - l + 1) % mod * i % mod;
            sum %= mod;
            sum += mod;
            sum %= mod;
        }
    }
    cout << sum << endl;
    return 0;
}