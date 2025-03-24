#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

// 负数在处理后数组中只能出现一段，所以要尽可能使负数直接倒置数组顺序的能力最大化
// 1 2 1 ：1
// 1 2 1 2 ：1
// 先查看是否递增，找到第一个不递增的地方，直接对后面全部乘x是否最优？最优，看上去
void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> processedCountFront(n + 1);
    vector<int> processedCountBack(n + 1);

    for (int& i : arr) {
        cin >> i;
    }
    if (n == 1) {
        cout << "0\n";
        return;
    }
    int cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        // cnt为处理完i+1处后需要的次数
        if (arr[i] >= arr[i + 1]) {
            cnt++;
        }
        processedCountFront[i + 1] = cnt;
    }
    // processedCountFront为处理完索引i位置至少需要的次数
    cnt = 0;
    for (int i = n - 2; i >= 0; i--) {
        // cnt为处理完i+1处后需要的次数
        if (arr[i] <= arr[i + 1]) {
            cnt++;
        }
        processedCountBack[i] = cnt;
    }
    int ans = INT32_MAX;
    for (int i = 0; i < n; i++) {
        int preone = processedCountBack[0] - processedCountBack[i - 1];    // [0,i-1]
        int sufone = processedCountFront[n - 1] - processedCountFront[i];  // [i,n-1]
        ans        = min(preone + sufone + 1, ans);
    }
    ans = min(min(processedCountBack[0] + 1, processedCountFront[n - 1]), ans);  // [0, n-1]
    cout << ans << '\n';
}

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}