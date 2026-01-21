#include <array>
#include <iostream>
#include <set>
#include <utility>
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
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll>   arr(m);
    multiset<ll> muse;
    for (int i = 0; i < m; i++) {
        cin >> arr[i];
        muse.ins(arr[i]);
    }
    vector<array<ll, 3>> brr(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 3; j++) cin >> brr[i][j];
    vector<array<ll, 3>> candi;
    ll                   cost = 0;
    for (int i = 0; i < n; i++) {
        k -= brr[i][1];
        brr[i][2] -= brr[i][1];
        cost += brr[i][2];
        candi.pb({brr[i][0], brr[i][2], i});
    }
    sort(all(candi), [](const auto& a, const auto& b) {
        if (a[1] == b[1]) {
            return a[0] < b[0];
        }
        return a[1] > b[1];
    });
    ll          tomore = cost - k;
    vector<int> finalvec;
    for (auto [wei, val, id] : candi) {
        auto it = muse.lower_bound(wei);
        if (it != muse.end()) {
            muse.erase(it);
            tomore -= val;
        } else {
            finalvec.pb(id);
        }
    }
    sort(all(finalvec), [&](int a, int b) { return brr[a][2] < brr[b][2]; });
    ll ans = n;
    while (tomore > 0) {
        tomore -= brr[finalvec.back()][2];
        finalvec.pop_back();
        ans--;
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