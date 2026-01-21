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
int           R;
constexpr int MAXN = 1e7 + 7;
int           fac[MAXN];
int           facz[MAXN];
int           minp[MAXN];
int           phi[MAXN], phiz[MAXN];
vector<int>   primes;

int qmi(i64 x, unsigned q, const i64 M = R)
{
    ll res = 1;
    for (; q; q >>= 1, x = x * x % M) {
        if (q & 1) res = res * x % M;
    }
    return (int)res;
}

void init()
{
    fac[0]  = 1;
    facz[0] = 0;
    phi[0]  = 1;
    phiz[0] = 0;
    for (ll i = 2; i < MAXN; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.pb(i);
        }

        for (ll p : primes) {
            if (i * p >= MAXN) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
    for (ll i = 1; i < MAXN; i++) {
        ll u = i, k = 0;
        while (u % R == 0) u /= R, k++;
        fac[i]  = (int)(fac[i - 1] * u % R);
        facz[i] = facz[i - 1] + k;
        u = (minp[i] != i ? i : i - 1), k = 0;
        while (u % R == 0) u /= R, k++;
        phi[i]  = phi[i - 1] * u % R;
        phiz[i] = phiz[i - 1] + k;
    }
}

void solve()
{
    i64 n, m;
    cin >> n >> m;
    i64 ans = 1ll * phi[m] * fac[n] % R * qmi(fac[m], R - 2) % R;
    if (facz[n] + phiz[m] - facz[m] != 0) {
        ans = 0;
    }
    cout << ans << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t >> R;
    init();
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