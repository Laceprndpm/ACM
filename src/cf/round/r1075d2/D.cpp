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
constexpr int P   = 1e9 + 7;

int fact[int(2e5 + 50)];

i64 qpow(i64 n, i64 q, i64 mod = P)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

void solve()
{
    // 从小到大考虑
    // 首先第一个一定是1
    // 随后考虑前面已经被全部满足了，遇到了一些0
    // 1001
    // 那么只能是0321，0231？共性就是第一个0的数1，中间必须隔这么多数，其中内部的数的顺序任意
    // 2^p * factor
    //
    // 分解质因数
    //
    ll n, c;
    cin >> n >> c;
    string s;
    cin >> s;
    s = '#' + s;
    if (s[1] == '0' || s[n] == '0') {
        cout << -1 << '\n';
        return;
    }
    int         cnt2 = 0;
    vector<int> prefix(n + 2);
    ll          ans = 1;
    for (int i = 2; i <= n;) {
        if (s[i] == '1') {
            cnt2++;
            ans *= 2;
            ans %= P;
            i++;
        } else {
            int j = i;
            while (s[j] == '0') {
                j++;
            }
            prefix[i - 1] += 1;
            prefix[j - 1] -= 1;
            ans *= fact[j - 2];
            ans %= P;
            ans *= qpow(fact[i - 2], P - 2);
            ans %= P;
            i = j;
        }
    }
    for (int i = 1; i <= n + 1; i++) {
        prefix[i] += prefix[i - 1];
    }
    prefix[2] += cnt2;
    for (int i = 2; i <= n; i++) {
        while (gcd(i, c) != 1 && prefix[i] != 0) {
            c /= gcd(i, c);
            prefix[i]--;
        }
    }
    if (c != 1) {
        cout << ans << '\n';
    } else {
        cout << -1 << '\n';
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
    fact[0] = 1;
    for (ll i = 1; i <= 2e5; i++) {
        fact[i] = fact[i - 1] * i % P;
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