#include <array>
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

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 只要sort就可以直接全部放进去吗？
    // 假如已知最小要k瓶
    // C(100, 50)不可计算
    // 从i开始遍历，
    //
    // dp[i]是浪费了i空间时，最少花的时间
    // dp[i][j]是清空i瓶时，至少导出j体积水
    // 假如已知i,j有一个空
    // 如果 s_i < s_j 且 v_i < v_j，则一定让i到j
    // 如果s_i < s_j 但 v_i > v_j,则可能让i进j来满足k,或让j进i当容量充裕时
    //
    // dp[i]为导出i体积水，最少浪费j空间
    //
    // dp[i][j]排空i，浪费j空间，至少需要val的时间
    //
    //

    vector<vector<i64>> dp(105, vector<i64>(10050, INF));
    int                 n;
    cin >> n;
    vector<array<int, 2>> arr(n);
    i64                   v_total = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i][0];
        v_total += arr[i][0];
    }
    for (int i = 0; i < n; i++) {
        cin >> arr[i][1];
    }
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j >= 0; j--) {
            for (int l = 10000 - arr[i][1]; l >= 0; l--) {
                dp[j + 1][l + arr[i][1]] = min(dp[j + 1][l + arr[i][1]], dp[j][l] + arr[i][0]);
            }
        }
    }
    sort(all(arr), [&](const auto& a, const auto& b) {
        return a[1] > b[1];
    });
    int k       = 0;
    i64 contain = 0;
    for (; k < n; k++) {
        contain += arr[k][1];
        if (contain >= v_total) {
            break;
        }
    }
    k++;
    i64 contain_total = 0;
    for (int i = 0; i < n; i++) {
        contain_total += arr[i][1];
    }
    i64 ans = INF;
    for (int i = 0; i <= contain_total - v_total; i++) {
        ans = min(ans, dp[n - k][i]);
    }
    cout << k << ' ';
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