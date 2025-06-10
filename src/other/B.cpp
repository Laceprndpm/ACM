// #include <bits/stdc++.h>

// namespace FastIO {
// template <typename T>
// inline T read()
// {
//     T    x = 0, w = 0;
//     char ch = getchar();
//     while (ch < '0' || ch > '9')
//         w |= (ch == '-'), ch = getchar();
//     while ('0' <= ch && ch <= '9')
//         x = x * 10 + (ch ^ '0'), ch = getchar();
//     return w ? -x : x;
// }

// template <typename T>
// inline void write(T x)
// {
//     if (!x) return;
//     write<T>(x / 10), putchar(x % 10 ^ '0');
// }

// template <typename T>
// inline void print(T x)
// {
//     if (x < 0)
//         putchar('-'), x = -x;
//     else if (x == 0)
//         putchar('0');
//     write<T>(x);
// }

// template <typename T>
// inline void print(T x, char en)
// {
//     if (x < 0)
//         putchar('-'), x = -x;
//     else if (x == 0)
//         putchar('0');
//     write<T>(x), putchar(en);
// }
// };  // namespace FastIO

// using namespace FastIO;

// #define MAXN 201
// int fa[MAXN], dep[MAXN];
// int c1[MAXN], c2[MAXN], len[MAXN];

// void solve()
// {
//     int       N = read<int>();
//     long long w = read<long long>();
//     for (int i = 2; i <= N; ++i)
//         fa[i] = read<int>();
//     for (int i = 2; i <= N; ++i)
//         dep[i] = dep[fa[i]] + 1;
//     for (int i = 1; i <= N; ++i)
//         len[i] = c1[i] = 0;
//     for (int i = 1, x, y; i <= N; ++i) {
//         x = i, y = (i == N ? 1 : i + 1);
//         while (x != y) {
//             if (dep[x] < dep[y]) std::swap(x, y);
//             (c1[x] ? c2[x] : c1[x]) = i, x = fa[x], ++len[i];
//         }
//     }
//     long long sum = 0, sur = N;
//     for (int i = 1, x; i < N; ++i) {
//         x = read<int>(), sum += read<long long>();
//         if ((--len[c1[x]]) == 0) --sur;
//         if ((--len[c2[x]]) == 0) --sur;
//         print<long long>(sum * 2 + sur * (w - sum), " \n"[i == N - 1]);
//     }
// }

// int main()
// {
//     int T = read<int>();
//     while (T--)
//         solve();
//     return 0;
// }

// // 2 * w = 18
// // 18 + (9-2)

// // 100 - 17 = 83
// // 83 * 3 + 200
#include <bits/stdc++.h>

using i64 = long long;

void solve()
{
    int n;
    i64 w;
    std::cin >> n >> w;

    std::vector<int>              p(n);
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
        adj[p[i]].push_back(i);
    }

    int cur = 0;

    std::vector<std::vector<int>> f(n);
    std::vector<int>              cnt(n);
    std::vector<i64>              dis(n);
    auto                          dfs = [&](auto &&self, int x) -> void {
        cur++;
        for (auto y : adj[x]) {
            f[y].push_back(cur - 1);
            cnt[cur - 1]++;
            self(self, y);
            f[y].push_back(cur - 1);
            cnt[cur - 1]++;
        }
    };
    dfs(dfs, 0);

    i64 sum = 0;
    int tot = n;
    for (int i = 1; i < n; i++) {
        int x;
        i64 y;
        std::cin >> x >> y;
        x--;
        for (auto j : f[x]) {
            cnt[j]--;
            dis[j] += y;
            if (cnt[j] == 0) {
                tot--;
            }
        }
        sum += y;
        std::cout << w * tot + sum * (2 - tot) << " \n"[i == n - 1];
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