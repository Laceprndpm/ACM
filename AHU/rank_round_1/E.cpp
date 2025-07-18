#include <iostream>
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
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    bool has_right = 0;
    bool all_right = 1;
    int  l = 1, r = n;
    while (l <= n && arr[l] == l) {
        l++;
    }
    while (r >= l && arr[r] == r) {
        r--;
    }
    for (int i = l; i <= r; i++) {
        if (arr[i] == i) {
            has_right = 1;
        } else {
            all_right = 0;
        }
    }
    if (all_right) {
        cout << "0\n";
        return;
    } else if (has_right) {
        cout << "2\n";
        return;
    } else {
        cout << "1\n";
    };
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
    // 头尾的完全正确的是否确实没必要选择？
    // 大抵是的
    // 如果头不对
    // 那么第一步就是先选中
    //
    // 总次数是否小于2?
    // 如果没有一个元素在原地，那么肯定可以1
    // 如果有若干元素在原地，是否可以全部打乱后(>1)，再一步解决？
    // 原地元素>1可以轻松打乱
    // 如果将原地元素和非原地元素一起打乱是否能解除限制？
    // 2 1 3
    // 1
    // 3 1 2
    // 1 2 3
    //
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