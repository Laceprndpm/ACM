#include <bits/stdc++.h>

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

void solve()
{
    int n;
    std::cin >> n;

    std::vector p(3, std::vector<int>(n)), invp(3, std::vector<int>(n));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> p[i][j];
            p[i][j]--;
            invp[i][p[i][j]] = j;
        }
    }

    std::vector<std::array<int, 2>> g(n, {-1, -1});
    g[0] = {0, 0};

    int mx[3]{p[0][0], p[1][0], p[2][0]};
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            if (mx[j] > p[j][i]) {
                g[i] = {j, invp[j][mx[j]]};
            }
        }
        if (g[i][0] != -1) {
            for (int j = 0; j < 3; j++) {
                mx[j] = std::max(mx[j], p[j][i]);
            }
        }
    }

    if (g[n - 1][0] == -1) {
        std::cout << "NO\n";
        return;
    }
    std::vector<std::array<int, 2>> ans;

    for (int i = n - 1; i;) {
        auto [j, x] = g[i];
        ans.push_back({j, i});
        i = x;
    }

    std::reverse(ans.begin(), ans.end());

    std::cout << "YES\n";
    std::cout << ans.size() << "\n";
    for (auto [x, y] : ans) {
        std::cout << "qkj"[x] << " " << y + 1 << "\n";
    }
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