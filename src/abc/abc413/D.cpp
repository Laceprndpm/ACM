#include <algorithm>
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
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(all(arr), [&](int a, int b) {
        return abs(a) < abs(b);
    });
    // a2 / a1 = ai + 1 / ai
    bool flag = 1;
    for (int i = 1; i < n - 1; i++) {
        if (1ll * arr[i] * arr[1] != 1ll * arr[i + 1] * arr[0]) {
            flag = 0;
        }
    }
    if (!flag) {
        bool allsame = 1;
        int  cnt1    = 0;
        for (int i = 0; i < n; i++) {
            if (abs(arr[0]) != abs(arr[i])) {
                allsame = 0;
            }
            if (arr[i] > 0) {
                cnt1++;
            }
        }
        if (allsame && ((cnt1 == n / 2) || (n - cnt1 == n / 2))) {
            cout << "Yes\n";
            return;
        }
    }
    if (flag) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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