#include <bits/stdc++.h>

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::map<int, int>            id;
    std::vector<int>              val;
    std::vector<std::vector<int>> adj;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;

        std::vector<std::array<int, 2>> ps;
        int                             x = a;
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                int t = 0;
                while (x % j == 0) {
                    t++;
                    x /= j;
                }
                ps.push_back({j, t});
            }
        }
        if (x > 1) {
            ps.push_back({x, 1});
        }

        std::vector<std::array<int, 2>> ds;
        auto                            dfs = [&](auto &&self, int i, int d, int v) -> void {
            if (i == ps.size()) {
                ds.push_back({v, d});
                return;
            }
            auto [p, e] = ps[i];
            for (int j = 0; j <= e; j++) {
                if (j) {
                    d *= p;
                    v++;
                }
                self(self, i + 1, d, v);
            }
        };
        dfs(dfs, 0, 1, 0);
        std::sort(ds.begin(), ds.end());
        ans += ds.back()[0];
        if (ds.size() > n) {
            ds.resize(n);
        }
        for (auto [v, d] : ds) {
            if (!id.contains(d)) {
                id[d] = adj.size();
                adj.push_back({});
                val.push_back(v);
            }
            adj[id[d]].push_back(i);
        }
    }

    std::vector<int> p(val.size());
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) { return val[i] < val[j]; });

    std::vector<int>  yx(n, -1);
    std::vector<bool> vis(val.size());
    auto              find = [&](auto &&self, int x) -> bool {
        vis[x] = true;
        for (auto y : adj[x]) {
            if (yx[y] == -1 || (!vis[yx[y]] && self(self, yx[y]))) {
                yx[y] = x;
                return true;
            }
        }
        return false;
    };

    for (auto i : p) {
        if (find(find, i)) {
            vis.assign(val.size(), false);
            ans -= val[i];
        }
    }
    std::cout << ans << "\n";

    return 0;
}
