#include <functional>
#include <iostream>
#include <numeric>
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
    int n, X;
    cin >> n >> X;
    vector<i64> arr(n);
    for (ll& i : arr) {
        cin >> i;
    }
    i64 sum = accumulate(all(arr), 0ll);
    sort(all(arr), greater<>());
    int        k   = sum / X;
    ll         res = 0;
    vector<ll> a, b;
    for (int i = 0; i < k; i++) {
        res += arr[i];
        a.pb(arr[i]);
    }
    for (int i = k; i < n; i++) {
        b.pb(arr[i]);
    }
    ll cur = 0;

    vector<ll> ansv;
    int        ptr  = 0;
    int        ptr0 = 0;
    for (; ptr0 < n - k;) {
        ll ccb = b[ptr0];
        if (cur + ccb >= X) {
            ansv.pb(a[ptr]);
            cur += a[ptr++];
            cur -= X;
        } else {
            cur += ccb;
            ansv.pb(ccb);
            ptr0++;
        }
    }
    while (ptr < k) {
        ansv.pb(a[ptr++]);
    }
    cout << res << '\n';
    for (ll i : ansv) {
        cout << i << ' ';
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