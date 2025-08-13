#include <cassert>
#include <cstdint>
#include <cstdio>
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

constexpr int U = (1 << 30) - 1;

void solve()
{
    int n, A, B, C;
    scanf("%d %d %d %d", &n, &A, &B, &C);
    int fi_vec[4];
    fi_vec[3] = A & U;
    fi_vec[2] = B & U;
    fi_vec[1] = C & U;
    int ans   = 0;
    for (int i = 0; i < 4 * n; i++) {
        int gi     = fi_vec[3] ^ ((fi_vec[3] << 16) & U);
        int hi     = gi ^ (gi >> 5);
        fi_vec[0]  = hi ^ ((hi << 1) & U) ^ fi_vec[2] ^ fi_vec[1];
        int cur_fi = fi_vec[0];
        if (i < n) {
            if (cur_fi % (n - i) != 0) {
                ans ^= 1;
            }
        } else {
            assert(i >= n);
            if (i == n) {
                printf("%d", ans);
            } else if ((i - n) % 3 == 0) {
                int l  = min(fi_vec[3] % n, fi_vec[2] % n);
                int r  = max(fi_vec[3] % n, fi_vec[2] % n);
                int di = fi_vec[1] % n + 1;
                if ((r - l + 1) % 2 == 0 && di % 2 == 1) {
                    ans ^= 1;
                }
                printf("%d", ans);
            }
        }
        for (int j = 3; j >= 1; j--) {
            fi_vec[j] = fi_vec[j - 1];
        }
    }
    putchar('\n');
}

signed main(signed argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    scanf("%d", &t);
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