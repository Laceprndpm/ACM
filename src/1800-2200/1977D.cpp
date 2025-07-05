#include <algorithm>
#include <array>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
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

constexpr int INF = 1e9;

inline void hash_combine(std::size_t& seed) {}

template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, const Rest&... rest)
{
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    hash_combine(seed, rest...);
}

namespace std {
template <>
struct hash<array<i64, 2>> {
    std::size_t operator()(const std::array<i64, 2>& a) const noexcept
    {
        std::size_t seed = 0;
        hash_combine(seed, a[0], a[1]);
        return seed;
    }
};
}  // namespace std

void solve()
{
    int n, m;
    cin >> n >> m;
    std::vector<int> primes = {999999937, 999999929, 999999893, 999999883, 999999881,
                               999999863, 999999857, 999999853, 999999841, 999999797};
    int              idx1   = rand() % 10;
    int              idx2;
    do {
        idx2 = rand() % 10;
    } while (idx2 == idx1);
    const i64      MOD1 = primes[idx1];
    const i64      MOD2 = primes[idx2];
    vector<i64>    power2MOD_1(n), power2MOD_2(n);
    vector<string> bd(n);
    for (int i = 0; i < n; i++) {
        cin >> bd[i];
    }
    power2MOD_1[0] = power2MOD_2[0] = 1;
    for (int i = 1; i < n; i++) {
        power2MOD_1[i] = power2MOD_1[i - 1] * 2 % MOD1;
        power2MOD_2[i] = power2MOD_2[i - 1] * 2 % MOD2;
    }
    unordered_map<array<i64, 2>, pair<int, pair<int, int>>> mp;
    mp.reserve(n * m);
    for (int j = 0; j < m; j++) {
        array<i64, 2> sum = {0, 0};
        for (int i = 0; i < n; i++) {
            if (bd[i][j] == '1') {
                sum[0] = (sum[0] + power2MOD_1[i]) % MOD1;
                sum[1] = (sum[1] + power2MOD_2[i]) % MOD2;
            }
        }
        for (int i = 0; i < n; i++) {
            auto cur = sum;
            if (bd[i][j] == '1') {
                cur[0] = (cur[0] - power2MOD_1[i] + MOD1) % MOD1;
                cur[1] = (cur[1] - power2MOD_2[i] + MOD2) % MOD2;
            } else {
                cur[0] = (cur[0] + power2MOD_1[i]) % MOD1;
                cur[1] = (cur[1] + power2MOD_2[i]) % MOD2;
            }
            mp[cur].first++;
            mp[cur].second = {i, j};
        }
    }
    auto mx = pair<int, pair<int, int>>{0, pair<int, int>{0, 0}};
    for (auto [_, val] : mp) {
        mx = max(val, mx);
    }
    auto [x, y] = mx.second;
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        ans[i] = bd[i][y] - '0';
    }
    ans[x] ^= 1;
    cout << mx.first << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i];
    }
    cout << '\n';
}

signed main(signed argc, char** argv)
{
    srand(time(0));
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