#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

constexpr int P     = 1000000007;
constexpr int inv10 = 700000005;

int power(int a, int b)
{
    int res = 1;
    for (; b; b /= 2, a = i64(a) * a % P) {
        if (b % 2) {
            res = i64(res) * a % P;
        }
    }
    return res;
}

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n + 2), b(n + 2);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        a[i] = i64(a[i]) * inv10 % P;
        b[i] = i64(a[i]) * power(1 - a[i], P - 2) % P;
    }
    b[n + 1] = 1;

    int mul = 1;
    for (int i = 1; i <= n; i++) {
        if (a[i] != 1) {
            mul = i64(mul) * (1 - a[i]) % P;
        }
    }

    std::vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cnt[i] = cnt[i - 1] + (a[i] == 1);
    }

    std::vector<int> f(n + 1);

    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        if (cnt[r] - cnt[l - 1] == 0) {
            f[r] = std::max(f[r], l);
        }
    }

    for (int i = 1; i <= n; i++) {
        f[i] = std::max(f[i], f[i - 1]);  // 最远从哪里转移
    }

    // dp[i]为合法，且最后一个染色的点为i
    std::vector<int> dp(n + 2), pre(n + 2);  // dp[i] = [1, i]点全部合法
    dp[0]  = 1;
    pre[0] = 1;
    for (int i = 1; i <= n + 1; i++) {  // i-1 -> i
        dp[i]  = i64(pre[i - 1] - (f[i - 1] ? pre[f[i - 1] - 1] : 0)) * b[i] % P;
        pre[i] = (pre[i - 1] + dp[i]) % P;
    }

    int ans = i64(dp[n + 1]) * mul % P;
    if (ans < 0) {
        ans += P;
    }
    std::cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
