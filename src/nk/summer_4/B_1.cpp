#include <bits/stdc++.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

// vectors
#define len(x)  int(x.size())
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()
#define mt      make_tuple
#define fi      first
#define se      second

// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

constexpr int INF = 1e9;

namespace detail {

// 检测是否可迭代
template <class T, class = void>
struct is_iterable : std::false_type {};

template <class T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin())>> : std::true_type {};

// 递归打印
template <class T>
void smart_print(std::ostream& os, const T& val, int indent = 0)
{
    if constexpr (is_iterable<T>::value && !std::is_same_v<T, std::string>) {
        if (indent == 0) {
            os << '\n';
        }
        using element_type   = typename T::value_type;
        constexpr bool is_2d = is_iterable<element_type>::value;
        os << (is_2d ? "[\n" : "[");
        for (auto it = val.begin(); it != val.end();) {
            if constexpr (is_2d) os << std::string(indent + 2, ' ');
            smart_print(os, *it, indent + 2);
            if (++it != val.end()) os << (is_2d ? ",\n" : ", ");
        }
        os << (is_2d ? "\n" + std::string(indent, ' ') : "") << "]";
    } else {
        os << val;  // 基础类型直接输出
    }
}
}  // namespace detail

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

void flush()
{
    std::cerr.flush();
}

template <class T>
void dbg_wt(const T& val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print()
{
    dbg_wt('\n');
}

template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail)
{
    dbg_wt(head);
    if (sizeof...(Tail)) dbg_wt(' ');
    print(forward<Tail>(tail)...);
}

#if defined(DEBUG)
#define dbg(...)                                    dbg_IMPL(__VA_ARGS__, dbg6, dbg5, dbg4, dbg3, dbg2, dbg1)(__VA_ARGS__)
#define dbg_IMPL(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define dbg1(x)                                     print(#x, "=", (x)), flush()
#define dbg2(x, y)                                  print(#x, "=", (x), #y, "=", (y)), flush()
#define dbg3(x, y, z)                               print(#x, "=", (x), #y, "=", (y), #z, "=", (z)), flush()
#define dbg4(x, y, z, w)                            print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w)), flush()
#define dbg5(x, y, z, w, v)                         print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v)), flush()
#define dbg6(x, y, z, w, v, u) \
    print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v), #u, "=", (u)), flush()
#else
#define dbg(...)
#endif
/**
 * @brief 并查集
 * 0-index
 */
struct DSU {
    int              component;
    std::vector<int> f, siz;

    DSU() {}

    DSU(int n) : component(n)
    {
        init(n);
    }

    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x)
    {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        component--;
        return true;
    }

    int size(int x)
    {
        return siz[find(x)];
    }

    std::vector<std::vector<int>> getGroups(void)
    {
        std::vector<std::vector<int>>   res;
        std::map<int, std::vector<int>> groups;
        for (int i = 0; i < f.size(); i++) {
            groups[find(i)].emplace_back(i);
        }
        res.reserve(groups.size());
        for (auto& [_, group] : groups) {
            res.emplace_back(std::move(group));
        }
        return res;
    }
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> board(n + 2);
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        s        = ' ' + s + '1';
        board[i] = std::move(s);
    }
    board[0] = board[n + 1] = string(m + 2, '1');
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = j;
        }
    }

    for (int i = 1; i <= n; i++) {
        dp[i][m] = -1;
    }
    // 假如我在这个点，最晚什么时候会失败？
    // 如果我要进入下一个点，对于所有最终走向失败的点，如果他失败的太早了，我就绝不会进去
    // 所以应该取max，如果取max后，还是小于视野，就看看周围有没有可以成功的
    //
    bool flag = 0;
    for (int j = m - 1; j >= 1; j--) {
        for (int i = 1; i <= n; i++) {
            if (board[i][j + 1] == '1') {
                continue;
            }
            dp[i][j] = max(dp[i][j], dp[i][j + 1]);
        }

        for (int i = n - 1; i >= 1; i--) {
            if (board[i + 1][j] == '1') {
                continue;
            }
            dp[i][j] = max(dp[i][j], dp[i + 1][j]);
        }
        for (int i = 2; i <= n; i++) {
            if (board[i - 1][j] == '1') {
                continue;
            }
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }

        for (int i = 1; i <= n; i++) {
            if (board[i][j + 1] == '1') {
                continue;
            }
            if (dp[i][j] - j < k) {
                if (dp[i][j + 1] == -1) {
                    dp[i][j] = -1;
                }
            }
        }
        for (int i = n - 1; i >= 1; i--) {
            if (board[i + 1][j] == '1') {
                continue;
            }
            if (dp[i][j] - j < k) {
                if (dp[i + 1][j] == -1) {
                    dp[i][j] = -1;
                }
            }
        }
        for (int i = 2; i <= n; i++) {
            if (board[i - 1][j] == '1') {
                continue;
            }
            if (dp[i][j] - j < k) {
                if (dp[i - 1][j] == -1) {
                    dp[i][j] = -1;
                }
            }
        }
        // dbg(dp);
    }
    for (int i = 1; i <= n; i++) {
        if (dp[i][1] != -1) {
            flag = 1;
        }
    }
    if (flag) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

signed main(signed argc, char** argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
