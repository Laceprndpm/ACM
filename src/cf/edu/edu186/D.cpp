#include <algorithm>
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
int           fac[91];
int           invfac[91];
constexpr int P = 998244353;

constexpr ll power(ll a, u64 b, ll res = 1)
{
    for (; b != 0; b /= 2, a *= a, a %= P) {
        if (b & 1) {
            res *= a;
            res %= P;
        }
    }
    return res;
}

ll binom(int n, int m)
{
    if (n < m || m < 0) return 0;
    return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 0; i < n + 1; i++) {
        cin >> arr[i];
    }
    auto it  = max_element(arr.begin() + 1, arr.end());
    ll   sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += *it - arr[i];
    }
    if (sum <= arr[0]) {
        cout << fac[n] << '\n';
        return;
    }
    sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += max(*it - 1 - arr[i], 0);
    }
    if (sum > arr[0]) {
        cout << 0 << '\n';
        return;
    } else {
        ll pool = arr[0] - sum;
        ll cnt  = count(arr.begin() + 1, arr.end(), *it);
        cout << 1ll * binom(pool + cnt, cnt) * fac[n - cnt] % P * fac[cnt] % P << '\n';
        return;
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
    fac[0] = 1;

    for (int i = 1; i <= 90; i++) {
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[90] = power(fac[90], P - 2);
    for (int i = 89; i >= 0; i--) {
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }
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