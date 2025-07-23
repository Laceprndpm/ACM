#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>

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

struct Basis {
    bool flag;  // 可以表示0

    static constexpr int MN = 60;

    u64 basis_arr[MN + 1];
    u64 tmp[MN + 1];

    void init()
    {
        memset(basis_arr, 0, sizeof(basis_arr));
        flag = 0;
    }

    void retreat(int idx)
    {
        basis_arr[idx] = 0;
    }

    int insert(u64 x)
    {
        for (int i = MN; i >= 0; i--)
            if (x & (1ull << i)) {
                if (!basis_arr[i]) {
                    basis_arr[i] = x;
                    return i;
                } else {
                    x ^= basis_arr[i];
                }
            }
        flag = true;
        return -1;
    }

    bool check(u64 x)
    {
        for (int i = MN; i >= 0; i--)
            if (x & (1ull << i)) {
                if (!basis_arr[i])
                    return false;
                else
                    x ^= basis_arr[i];
            }
        return true;
    }

    u64 qmax(u64 res = 0)
    {
        for (int i = MN; i >= 0; i--)
            res = max<u64>(res, res ^ basis_arr[i]);
        return res;
    }

    u64 qmin(u64 res = 0)
    {
        if (flag) return 0;
        for (int i = 0; i <= MN; i++)
            if (basis_arr[i]) return basis_arr[i];
        assert(0);
    }

    // -1ull为无值
    u64 query(u64 k)
    {
        u64 res = 0;
        int cnt = 0;
        k -= flag;
        if (!k) return 0;
        for (int i = 0; i <= MN; i++) {
            for (int j = i - 1; j >= 0; j--)
                if (basis_arr[i] & (1ull << j)) basis_arr[i] ^= basis_arr[j];
            if (basis_arr[i]) tmp[cnt++] = basis_arr[i];
        }
        if (k >= (1ull << cnt)) return -1ull;
        for (int i = 0; i < cnt; i++)
            if (k & (1ull << i)) res ^= tmp[i];
        return res;
    }
} b;

u64 arr[50];
u64 ans = 0;
int n;

void dfs(int cur)
{
    if (cur >= n) {
        ans = max<u64>(ans, b.qmax());
        return;
    }
    int idx1 = b.ins(arr[cur]);
    dfs(cur + 2);
    if (idx1 != -1) b.retreat(idx1);
    if (cur + 1 < n) {
        int idx2 = b.ins(arr[cur + 1]);
        dfs(cur + 3);
        if (idx2 != -1) b.retreat(idx2);
    }
}

void solve()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%llu", (unsigned long long*)(arr + i));
    }
    b.init();
    ans = 0;
    dfs(0);
    printf("%llu\n", (unsigned long long)ans);
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