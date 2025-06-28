#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
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

int LIS(vector<int>& a)
{
    vector<int> dp(1e6 + 50, INF);
    int         mx = dp[0];
    for (int i = 0; i < sz(a); ++i) {
        *std::upper_bound(all(dp), a[i]) = a[i];
    }
    int ans = 0;
    while (dp[ans] != mx)
        ++ans;
    return ans;
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
    int n;
    cin >> n;
    vector<int> arr(n), brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i] >> brr[i];
        if (arr[i] > brr[i]) swap(arr[i], brr[i]);
    }
    vector<pair<int, int>> vec;
    for (int i = 0; i < n; i++) {
        vec.push_back({arr[i], brr[i]});
        vec.push_back({brr[i], arr[i] + 2 * n});
    }
    sort(all(vec), greater<>());
    vector<int> vec2;
    for (auto i : vec) {
        vec2.push_back(i.second);
    }
    cout << LIS(vec2);
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */