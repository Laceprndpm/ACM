#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr int MOD = 1e9 + 7;

i64 rev(int n, i64 p)
{
    list<int> postion;
    int       cnt = 0;
    while (n) {
        postion.push_back(n % p);
        n /= p;
        cnt++;
    }
    i64 ans = 0;
    i64 q   = 1;
    while (cnt--) {
        ans += postion.back() * q;
        postion.pop_back();
        ans %= MOD;
        q *= p;
        q %= MOD;
    }
    return ans;
}

void solve()
{
    i64 n, k;
    i64 ans = 0;
    cin >> n >> k;
    if (k <= n) {
        for (int i = 2; i <= k; i++) {
            ans += rev(n, i);
            ans %= MOD;
        }
    } else {
        for (int i = 2; i <= n; i++) {
            ans += rev(n, i);
            ans %= MOD;
        }
        ans += ((k - n) % MOD) * n % MOD;
        ans %= MOD;
    }
    cout << ans << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}