#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
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
#define int     long long
constexpr int INF = 1e9;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 获取当前最小为mn
    // 若当前种类为5
    // 则对于这5个数，若%5各不相同
    // 假如剩俩种数，%2各不相同，则无法通过-2来归一化
    // 又看错题
    //
    // 相同数没有意义
    // 第一个变成0的数有贡献，之后都没有贡献
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    set<int> st;
    for (int i : arr) {
        st.insert(i);
    }
    int curM = 0;
    int x    = (int)st.size();
    int ans  = 0;
    if (x == 1) {
        cout << 0 << '\n';
        return 0;
    }
    for (auto it = st.begin(); it != st.end();) {
        int steps = (*it + x - 1 - curM) / x;
        curM += steps * x;
        ans += steps;
        while (it != st.end() && *it <= curM) {
            if (it == st.begin()) x++;
            it++;
            x--;
        }
    }
    cout << ans << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */