#include <iostream>
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

void solve()
{
    // 大大两两匹配，则最多活(n // 2)个？
    // 大小匹配构造环，最少活多少个？2->1，3->2,4->3，只可以活1个
    // 如何0存活？/
    // 让次大先攻击外部的，然后让大的攻击次大，此时次次大去打大，应该是唯一的方法。即当且仅当次大+次次大>=大有几乎清空
    //
    int n, m;
    cin >> n >> m;
    vector<ll> arr(n + 1);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    vector<int> idx(n + 1);
    iota(all(idx), 0);
    sort(idx.begin() + 1, idx.end(), [&](int a, int b) { return arr[a] < arr[b]; });
    // 第一大的数确实可以对应第一大的下标，OK
    sort(arr.begin() + 1, arr.end());
    if (n / 2 < m) {
        cout << "-1\n";
        return;
    }
    vector<pair<int, int>> ans;
    if (m == 0) {
        if ((n <= 2 || arr[n] > accumulate(arr.begin() + 1, arr.begin() + n, 0ll))) {
            cout << "-1\n";
            return;
        }
        ll  tmp = arr[n];
        int i;
        for (i = n - 1; i >= 1; i--) {
            if (tmp <= arr[i]) break;
            ans.pb({i, n});
            tmp -= arr[i];
        }
        for (int j = 1; j <= i - 1; j++) {
            ans.pb({j + 1, j});
        }
        ans.pb({n, i});
    } else {
        int remain = m;
        int pre_k  = n - m * 2;
        for (int i = 1; i <= pre_k; i++) {
            ans.pb({i + 1, i});
        }
        for (int i = pre_k + 1; i <= n; i += 2) {
            ans.pb({i + 1, i});
        }
    }
    cout << ans.size() << '\n';
    for (auto [u, v] : ans) {
        cout << idx[u] << ' ' << idx[v] << '\n';
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