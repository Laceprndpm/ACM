#include <bits/stdc++.h>

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

void solve()
{
    int n;
    std::cin >> n;

    int ans = 0;
    for (i64 x = 1; x <= n + 1; x *= 10) {
        ans += std::min<i64>((n + 1) / x, 9);
    }
    ans--;
    for (int len = 2; len <= 8; len += 2) {
        std::string s;
        s += '9';
        s += std::string(len / 2, '0');
        s += std::string(len / 2 - 1, '9');
        for (int x = 1; x <= 8; x++) {
            s += '0' + x;
            if (std::stoi(s) <= n) {
                ans--;
            }
            s.pop_back();
        }
    }
    for (int len = 3; len <= 7; len += 2) {
        std::string s;
        s += '9';
        s += std::string(len / 2, '0');
        s += std::string(len / 2 - 1, '9');
        for (int x = 1; x <= 8; x++) {
            s += '0' + x;
            s += '9';
            if (std::stoi(s) <= n) {
                ans--;
            }
            s.pop_back();
            s.pop_back();
        }
    }

    int d[9];
    for (int i = 0, x = n; i < 9; x /= 10, i++) {
        d[i] = x % 10;
    }

    std::array<std::array<int, 2>, 10> dp{};
    for (int i = 8; i >= 1; i--) {
        int ni = n;
        for (int j = 0; j < i; j++) {
            ni /= 10;
        }

        std::array<std::array<int, 2>, 10> ndp{};
        for (int x = 1; x <= 9; x++) {
            for (i64 y = x; y <= ni; y *= 10) {
                ndp[x][y < ni]++;
            }
        }
        for (int x = 0; x < 10; x++) {
            for (int l = 0; l < 2; l++) {
                for (int y = x; y <= (l ? 9 : d[i]); y++) {
                    ndp[y][l || y < d[i]] += dp[x][l];
                }
            }
        }
        dp = ndp;
        if (i == 2) {
            for (int x = 0; x <= 9; x++) {
                ans += dp[x][0] * std::min(9, (n % 100 + 1) / 10);
                ans += dp[x][1] * 9;
            }
        }
    }
    for (int x = 0; x <= 9; x++) {
        ans += dp[x][0] * (std::min(d[0], 8) + 1);
        ans += dp[x][1] * 9;
    }

    std::cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}