#include <functional>
#include <iostream>
#include <type_traits>
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

constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        cin >> arr[i];
    }
    function<vector<int>(int, int)> dfs = [&](int depth, int start) -> vector<int> {
        if (depth == 0) {
            vector<int> tmp(1);
            tmp[0] = arr[start];
            return tmp;
        }
        auto l = dfs(depth - 1, start);
        auto r = dfs(depth - 1, start + (1 << (depth - 1)));
        if (l > r) {
            std::swap(l, r);
        }
        l.insert(l.end(), r.begin(), r.end());
        r.clear();
        return l;
    };
    auto res = dfs(n, 0);
    for (int i = 0; i < (1 << n); i++) {
        cout << res[i] << " \n"[i == (1 << n) - 1];
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