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

ll query(int l, int r)
{
    cout << "? " << l << ' ' << r << endl;
    ll res;
    cin >> res;
    return res;
}

void solve()
{
    // 可以得知拼接几次?不能，知道k+拼接次数
    // 假设k = 2
    // 则多次得到1 1 1 1 4 1 1 1 1 1 1 2 2 1 1 1 1 1，怎么办？似乎不合法，因为2 2距离4太远，不可能中途修改
    // 1 1 1 1 4 1 1 1 1 2 2 1 1 1 1 1 1 1 1
    // 假设k = 1，则只存在1 2
    // 如果我逐次二分，每次平分需要log(n)次，最多平分n次？
    // 每次进入平分前，总和是知道的，且总是优先按照拼接脉络进行平分
    // 如果知道拼了5次，那么每次都只需要看小的那边就行
    // 因为拼接后还修改的话，那么一定不是
    // 验证：平分后，小的一定比大的优：
    // 如果A = B
    // A分裂k个大的，B分裂k+1,则len A < len B
    // 随后A = B = A + B
    // 一开始A = B
    // 所以分裂时确实更优
    //
    int n;
    cin >> n;
    auto spj = [&](int l, int r, ll sum) -> ll {
        ll base = query(l, l);
        if (base * (r - l + 1) == sum) {
            return base;
        }
        int pl = l, pr = r - 1;
        while (pl < pr) {
            int mid = (pl + pr + 1) / 2;
            ll  lft = query(l, mid);
            if (lft == base * (mid - l + 1)) {
                pl = mid + 1;
            } else {
                pr = mid;
            }
        }
        return query(pl, pl);
    };
    auto dfs = [&](auto&& self, int l, int r, ll sum) -> ll {
        if (l == r) return sum;
        int pl = l, pr = r - 1;
        ll  anspos = -1;
        while (pl < pr) {
            int mid = (pl + pr) / 2;
            ll  lft = query(l, mid);
            ll  rgt = sum - lft;
            if (lft > rgt) {
                pr = mid - 1;
            } else if (lft < rgt) {
                pl = mid + 1;
            } else {
                anspos = pl = pr = mid;
            }
        }
        if (anspos == -1 && query(l, pl) * 2 != sum) {
            return spj(l, r, sum);
        }
        int lftlen = pl - l + 1, rgtlen = r - pl;
        if (lftlen > rgtlen) {
            return self(self, pl + 1, r, sum / 2);
        }
        return self(self, l, pl, sum / 2);
    };
    ll res = dfs(dfs, 1, n, query(1, n));
    cout << "! " << res << endl;
}

// 4 1 1 1 1
signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
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