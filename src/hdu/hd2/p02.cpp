#include <bits/stdc++.h>

#include <iostream>

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

u64 lb(u64 x)
{
    return x & -x;
}

void solve()
{
    u64 a, b, n;
    cin >> n >> a >> b;
    if (a == b) {
        cout << 0 << '\n';
        return;
    }

    if (lb(a) == lb(b) || __builtin_popcountll(a) == __builtin_popcountll(b)) {
        cout << 1 << '\n';
        return;
    }

    u128 target_lb = lb(b);
    i64  target_cb = __builtin_popcountll(b);

    u128 cur_lb_a    = lb(a);
    i64  cur_count_a = __builtin_popcountll(a);

    // 先count，最优的应该就是把a的所有数都放在lb及其左侧
    u128 cur1 = 0;
    for (int i = 0; i < cur_count_a; i++) {
        cur1 |= target_lb << i;
        if (cur1 > n) break;
    }
    u128 cur2 = 0;

    // 先lowbit，最优的就是把a需要最少的数放在lba及其左侧
    for (int i = 0; i < target_cb; i++) {
        cur2 |= cur_lb_a << i;
        if (cur2 > n) break;
    }

    // 如果都不行，对于任意a,可以先lb调整到一位，然后count调整到b的lb，然后再lb调整到b
    if (cur1 > n && cur2 > n) {
        cout << 3 << '\n';
        return;
    } else {
        cout << 2 << '\n';
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