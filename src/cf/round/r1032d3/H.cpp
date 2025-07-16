#include <iostream>
#include <iterator>
#include <set>
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

constexpr int INF = 1e9 + 1;

void solve()
{
    int n;
    cin >> n;
    multiset<i64> mset;
    mset.insert(0);
    mset.insert(INF);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        auto it1 = mset.upper_bound(l);
        auto it2 = mset.upper_bound(r);
        mset.insert(l);
        auto it2_nxt = next(it2);
        if (*it2 != INF) {
            mset.erase(it2);
        }
        cout << sz(mset) - 2 << ' ';
    }
    cout << '\n';
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
    // dp[i]
    //
    // a1, a2, a3, a4, a5
    // 此时[l, r]
    // a1 <= l无效
    // a2 > l，变成a2 := l
    // a3 > l，a3 := a2
    //
    // a4 > r，a4 := a3
    //
    // a5 > r, a5 := a5
    //
    // a6 > r, a6 == a6
    // 所以每次的行为就是，shift一个区间后，再修改两端点
    // 可以用平衡树的插入和删除来实现吧
    //
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