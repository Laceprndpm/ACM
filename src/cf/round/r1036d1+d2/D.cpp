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
    int n, k;
    cin >> n >> k;
    vector<i64> arr(n);
    for (i64& i : arr) {
        cin >> i;
    }
    vector<i64> sorted_arr = arr;
    sor(sorted_arr);
    i64 kth = sorted_arr[k - 1];
    i64 idx = k - 1;
    while (idx < n && sorted_arr[idx] == sorted_arr[k - 1]) {
        idx++;
    }
    i64         num = idx - k + 1;
    vector<i64> brr;
    for (i64 i : arr) {
        if (i <= kth) brr.eb(i);
    }
    i64  i = 0, j = sz(brr) - 1;
    bool ok   = 1;
    i64  used = 0;
    for (; i <= j; i++, j--) {
        if (brr[i] == brr[j]) {
            continue;
        }
        if (brr[i] == kth) {
            j++;
            used++;
            continue;
        } else if (brr[j] == kth) {
            i--;
            used++;
            continue;
        } else {
            ok = 0;
        }
    }
    if (used > num) {
        ok = 0;
    }
    if (ok) {
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
    // 可以发现，只要x > kth ，就可以被移出，但
    // 当刚刚好它是第k小时，只能移一点点
    // 首先判断严格小于k的数是否回文
    // 如果是，则开始判断是否可以移出有限个kth来使其回文
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