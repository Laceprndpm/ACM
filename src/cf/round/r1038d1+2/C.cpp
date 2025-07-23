#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
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
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].fi >> points[i].se;
    }
    vector<int> idx(n);
    iota(all(idx), 0);
    sort(all(idx), [&](int a, int b) {
        return points[a].fi < points[b].fi;
    });
    vector<int> le(n / 2), ri(n / 2);
    for (int i = 0; i < n / 2; i++) {
        le[i] = idx[i];
        ri[i] = idx[i + n / 2];
    }

    sort(all(le), [&](int a, int b) {
        return points[a].se < points[b].se;
    });

    sort(all(ri), [&](int a, int b) {
        return points[a].se < points[b].se;
    });

    int  ptr_l = 0;
    int  ptr_r = 0;
    bool found = 0;
    for (; ptr_l < n / 2 && !found; ptr_l++) {
        while (ptr_r < n / 2 && points[ri[ptr_r]].se <= points[le[ptr_l]].se) {
            if (n / 2 - ptr_r == ptr_l) {
                found = 1;
                break;
            }
            ptr_r++;
        }
        if (n / 2 - ptr_r == ptr_l) {
            found = 1;
            break;
        }
    }
    if (n / 2 - ptr_r == ptr_l) {
        found = 1;
    }

    assert(found);

    for (int i = 0; i < ptr_l; i++) {
        cout << le[i] + 1 << ' ' << ri[i + ptr_r] + 1 << '\n';
    }

    for (int i = ptr_l; i < n / 2; i++) {
        cout << le[i] + 1 << ' ' << ri[i - ptr_l] + 1 << '\n';
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