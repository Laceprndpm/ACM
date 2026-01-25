#include <cassert>
#include <iostream>
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

void solve(int x = 0)
{
    // xx1和xx0，就行了？奇数会多一个1，偶数则可以让1和最高的搞？
    // 1 2
    // 2 1
    // 不行
    // 4 和 1不行，23行
    // 4和2
    // 等等，让我们考虑n=0b1000000，他可以和谁？
    // 等等，什么叫2 <= i <= n-1？
    // 那么此时，就只需要考虑m = 0b111111
    // 很明显pn = n
    // p1 = 2 3
    // p2 = 3 1
    // p3 = 1 2
    // 随后45,67...
    // 如果n = 0b10001
    // 直接搞就行，欧了

    // 草,i < j
    // 首先偶数还是只能pn = n？
    // 还是p1 = n？
    //
    // 令pn = 1
    // p(n-1) = n - 2
    // p(n-2) = n - 1
    // p_1 = n
    // 1 ^ n > n
    // 让n去尝试和2,3,4互换啥的
    //
    // 最终会多一个n,可以放1号位吗，可以
    // 奇数？
    // pn     = 1
    // pn - 1 = n
    // pn - 2 = n - 3
    // pn - 3 = n - 2
    // p2     = 3
    // p1 = n - 1
    int n;
    cin >> n;
    // if (x) {
    //     n = x;
    // }
    vector<int> ans(n + 1);
    if ((n & 1) == 0) {
        if (n == (n & (-n))) {
            cout << -1 << '\n';
            return;
        }
        // cout << n << ' ';
        ans[1] = n;
        for (int i = 2; i <= n - 1; i++) {
            ans[i] = (i ^ 1);
        }
        ans[n]   = 1;
        int flag = 1;
        for (int i = 2; i <= n && flag; i++) {
            if ((ans[i] ^ 1) <= n && (n ^ i) <= n) {
                swap(ans[1], ans[i]);
                flag = 0;
            }
        }
        assert(flag == 0);
    } else {
        ans[1] = n - 1;
        for (int i = 2; i <= n - 1; i++) {
            ans[i] = (i ^ 1);
        }
        ans[n] = 1;
    }
    for (int i = 1; i <= n; i++) {
        assert(i == n || (ans[i] ^ i) <= n);
        cout << ans[i] << ' ';
    }
    cout << '\n';
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