#include <bits/stdc++.h>

#include <iostream>
#include <utility>
#include <vector>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
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
#define mp      make_pair
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

constexpr i64 INF = 1e18;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    constexpr int FULL = 131071;
    vector<int>   wi(17);
    for (int i = 0; i < 17; i++) {
        cin >> wi[i];
    }
    int len;
    cin >> len;
    if (len % 2) len++;
    vector<int> bad(1 << 17);
    for (int l = 0; l + len - 1 < n; l++) {
        int  r       = l + len - 1;
        int  status  = 0;  // FULL ^ status为不对的选择，它的子集也是不对的
        bool already = 0;
        int  lp      = l;
        for (; lp <= r; l++, r--) {
            if (s[l] == s[r]) {
                already = 1;
            } else {
                char a = s[l], b = s[r];
                if (a > b) {
                    swap(a, b);
                }
                status |= 1ll << (a - 'a');
            }
        }
        if (already) {
            continue;
        }
        bad[FULL ^ status] = 1;
    }
    for (int i = FULL - 1; i >= 0; i--) {
        for (int j = 0; j < 17; j++) {
            bad[i] |= bad[i | 1 << j];
        }
    }
    i64 ans = INF;
    for (int i = 0; i < FULL; i++) {
        if (!bad[i]) {
            i64 cost = 0;
            for (int j = 0; j < 17; j++) {
                if (i >> j & 1) {
                    cost += wi[j];
                }
            }
            ans = min(ans, cost);
        }
    }
    cout << ans << '\n';
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
    // aacd
    // 001 100
    // 找到x,满足x
    // {a},{c}
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