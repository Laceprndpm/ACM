#include <initializer_list>
#include <iostream>
#include <map>
#include <numeric>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

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

constexpr int INF = 1e9;

i64 lcm(initializer_list<i64> arr)
{
    i64 ans = 1;
    for (i64 i : arr) {
        ans = lcm(ans, i);
    }
    return ans;
}

void solve()
{
    int n;

    cin >> n;
    map<int, int> mp1;
    i64           ans = 1;
    for (int i = 1; i <= n; i++) {
        // for (int j = 1; j <= n; j++) {
        //     for (int k = 1; k <= n; k++) {
        //         for (int q = 1; q <= n; q++) {
        ans *= i;
        //         }
        //     }
        // }
    }
    // 也许我可以枚举lcm
    // 如果lcm == 1
    // lcm == 2 ai可以为d(x)，即d(x) ** k - lcm1种 方法组成
    // ans = 2 ** (d(2) ** k - d(1) ** k)
    // 或者枚举gcd吗，似乎区别不大
    // 不,gcd <= 1e6
    // 枚举1-1e6的gcd
    // gcd == 1e6
    // 只能全部为1e6
    // 但是这个10**100是不是必然带100常数？
    // 如果a1,a2,a3...ak的gcd为x
    // 那么有多少种可能?
    // x在1e6内有p个倍数的话。。。
    // 似乎不太好预处理。。。
    // 那么就ai只能是1 或 2，同时去除lcm == 1的部分
    //
    // 预处理？
    //
    //
    //
    // 1 2 : 1
    //
    //
    // 2 1 : 2
    // 2 2 : 8
    // 2 3 : 128
    // 2 4 : 32768
    //
    // 3 1 : 6
    // 3 2 : 7776
    // 4 2 : 1146617856
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