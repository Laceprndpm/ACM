#include <bits/stdc++.h>
#define int     i64 /* R.I.P */
#define all(x)  std::begin(x), std::end(x)
#define rall(x) std::rbegin(x), std::rend(x)
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;

void solve()
{
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    if (n <= 3 || s == std::string(s[0], n)) {
        std::cout << 0 << "\n";
        return;
    }

    auto work = [&](char c) -> i64 {
        std::vector<int> pos;
        for (int i = 0; i < n; i++) {
            if (s[i] == c) {
                pos.push_back(i);
            }
        }

        auto calc = [&](int x) -> i64 {
            i64 res = 0;
            for (int i = 0; i < pos.size(); i++) {
                // std::cerr << pos[i] << "<->" << x + i << "]\n";
                res += std::abs(pos[i] - (x + i));
            }
            return res;
        };

        int l = 0, r = n - pos.size();
        i64 ans = 1e18;
        ans     = std::min(ans, calc(l));
        ans     = std::min(ans, calc(r));
        while (l <= r) {
            int lm = (l + l + r) / 3;
            int rm = (l + r + r) / 3;

            i64 lc = calc(lm);
            i64 rc = calc(rm);

            ans = std::min(ans, lc);
            ans = std::min(ans, rc);
            if (lc < rc) {
                r = rm - 1;
            } else {
                l = lm + 1;
            }
        }

        return ans;
    };

    std::cout << std::min(work('a'), work('b')) << "\n";
}

signed main(signed argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    std::cin.tie(0)->sync_with_stdio(false);
    int t = 1;
    std::cin >> t;
    while (t--) solve();
    return 0;
}