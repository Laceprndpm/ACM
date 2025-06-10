#include <cmath>
#include <deque>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr int MOD = 1e9 + 7;

i64 rev(i64 n, i64 p)
{
    deque<i64> q;
    while (n) {
        q.push_back(n % p);
        n /= p;
    }
    i64 ans = 0;
    while (!q.empty()) {
        ans *= p;
        ans += q.front();
        q.pop_front();
    }
    return ans;
}

i64 rev2(i64 n, i64 p)
{
    return (n % p) * p + n / p;
}

i64 sumfang(i64 x)
{
    return x * (x + 1) * (2 * x + 1) / 6ll;
}

void solve()
{
    i64 n, k;
    cin >> n >> k;
    i64 i     = 2;
    i64 ans   = 0;
    i64 bound = ceil(sqrt(n));
    for (; i <= bound && i <= k; i++) {
        ans += rev(n, i);
        ans %= MOD;
    }
    for (; i <= n && i <= k;) {
        i64 cur = n / i;
        i64 l = i, r = n / cur;
        r = min(k, r);
        ans += cur * (r - l + 1);
        ans -= cur * (sumfang(r) - sumfang(l - 1));
        ans += (r + l) * (r - l + 1) / 2 * n;
        i = r + 1;
    }
    ans %= MOD;

    ans += ((k - i + 1ll) % MOD) * n;
    ans %= MOD;
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