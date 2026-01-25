#include <cstdlib>
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

int are_you_gay(const vector<int>& arr)
{
    int res;
    cout << '?';
    for (int i = 1; i <= 100; i++) {
        cout << ' ' << arr[i];
    }
    cout << endl;
    cin >> res;
    if (res == -1) exit(0);
    return res;
};

void solve()
{
    // q1 ^ q2 = x ^ x ^ ai ^ bj = ai ^ bj
    // 如果ai < 0b100000，bj > 0b100000，那么就可以确定1 << 8
    vector<int> arr(101);
    vector<int> brr(101);
    for (int i = 1; i <= 100; i++) {
        arr[i] = i;
        brr[i] = (i << 7);
    }
    int res1 = are_you_gay(arr), res2 = are_you_gay(brr);
    int res = res1 ^ res2;
    res     = res & ((1 << 7) - 1);
    cout << "! " << (res ^ res1) << endl;
}

signed main(signed argc, char** argv)
{
    int t = 1;
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