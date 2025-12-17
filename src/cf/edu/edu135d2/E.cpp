#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
#ifndef CLANGD_MODE
#ifndef DEBUG
#define NDEBUG
#undef assert
#define assert(x) [[assume(x)]]
#include <bits/stdc++.h>
#endif
#endif
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

constexpr i64 INF = 1e16;

i64 exgcd(i64 a, i64 b, i64& x, i64& y)
{
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

template <typename T>
T floor(T a, T b)
{
    return a / b - (a % b && (a ^ b) < 0);
}

template <typename T>
T ceil(T x, T y)
{
    return floor(x + y - 1, y);
}

int ts(int L, int R, auto f)
{
    while (L + 2 < R) {
        int m1 = L + (R - L) / 3;
        int m2 = R - (R - L) / 3;
        if (f(m1) < f(m2)) {
            L = m1;
        } else {
            R = m2;
        }
    }
    i64 max_val = f(L);
    i64 max_idx = L;

    for (int i = L + 1; i <= R; ++i) {
        if (f(i) > max_val) {
            max_val = f(i);
            max_idx = i;
        }
    }

    return max_idx;
}

void solve()
{
    int n;
    cin >> n;
    vector<i64> arr(n + 1);
    vector<i64> brr(n + 1);
    vector<i64> contri(n + 1);
    vector<i64> prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i] >> brr[i];
        contri[i] = brr[i] - arr[i];
    }
    sort(contri.begin() + 1, contri.end(), greater<>());
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + contri[i];
    }
    int m;
    cin >> m;
    i64 sumarr = accumulate(all(arr), 0ll);
    for (int i = 0; i < m; i++) {
        i64 a, b;
        cin >> a >> b;
        i64 x0, y0;
        i64 r  = exgcd(a, b, x0, y0);
        i64 m  = n / r;
        i64 xp = x0 * m, yp = y0 * m;
        i64 bb = b / r, aa = a / r;
        // x = xp + k * b / r
        // y = yp - k * a / r
        i64 kl = ceil(-xp, bb), kr = floor(yp, aa);
        if (kl > kr || n % r != 0) {
            cout << -1 << '\n';
            continue;
        }
        auto check = [&](int k) -> i64 {
            i64 y   = yp - k * aa;
            i64 buy = y * b;
            if (buy < 0 || buy > n) return -INF;
            return prefix[buy];
        };
        while (kl < kr) {
            int mid = floor(kl + kr, 2ll);
            if (check(mid) >= check(mid + 1))
                kr = mid;
            else
                kl = mid + 1;
        }
        cout << check(kl) + sumarr << '\n';
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
    solve();
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */