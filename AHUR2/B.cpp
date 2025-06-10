#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
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
    // aj * aj = ai * ak
    //
    // aj / ai = ak / aj
    //
    // 对于每个数,sqrt一下，然后如果可以
    //
    // 1e3 ~ 1 = ai * ak?
    // 假如我算出来所有ai * ak <= 1e12 // O(1e6) T存在
    //
    // d(x)是什么级别的？
    // sqrt(x)
    //
    //
    //
    //
    int n;
    cin >> n;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    unordered_map<i64, i64> cnt;
    cnt.reserve(n);
    sor(arr);
    for (int i = 0; i < n; i++) {
        cnt[arr[i]]++;
    }
    arr.erase(unique(all(arr)), arr.end());
    i64 ans1 = 0;
    for (i64 i : arr) {  // TODO:考虑自身
        for (i64 j = 1; j <= sqrt(i); j++) {
            if (i % j == 0) {
                if (j != 1 && cnt.count(i / j) && cnt.count(i * j)) {
                    ans1 += cnt[i / j] * cnt[i * j] * cnt[i];
                }
                if (i / j != 1 && j * j != i && cnt.count(i / (i / j)) && cnt.count(i * (i / j))) {
                    ans1 += cnt[i / (i / j)] * cnt[i * (i / j)] * cnt[i];
                }
            }
        }
    }
    for (i64 i : arr) {
        if (cnt[i] >= 3) {
            ans1 += (cnt[i] - 2) * (cnt[i] - 1) * cnt[i];
        }
    }
    i64 ans2 = 0;
    for (i64 i : arr) {
        if (i % 24 == 0 && cnt.count(i / 24) && cnt.count(i * 24)) {
            ans2 += cnt[i] * cnt[i / 24] * cnt[i * 24];
        }
    }
    cout << ans1 << ' ' << ans2 << '\n';
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