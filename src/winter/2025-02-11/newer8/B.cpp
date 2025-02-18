#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

constexpr LL MOD = LLONG_MAX;

LL qpow(LL n, LL q, LL mod = MOD)
{
    if (q == 0) {
        return 1;
    }
    LL ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        cnt[temp]++;
    }
    LL ans = 1;
    for (int i = 1; i <= k; i++) {
        ans *= qpow(2, cnt[i]) - 1;
    }
    cout << ans;
    return 0;
}