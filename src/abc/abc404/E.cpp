#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 可以贪心的把当前碗里的豆子放到前面第一个非空碗
    int n;
    cin >> n;
    vector<int> cArr(n + 1);
    vector<int> aArr(n + 1);
    for (int i = 1; i < n; i++) {
        cin >> cArr[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> aArr[i];
    }
    vector<i64>                 dparr(n + 1, INF);
    function<i64(int u, int v)> dp = [&](int u, int v) -> i64 {
        dparr[v] = 0;
        for (int i = v; i >= u; i--) {
            int f = max(u, i - cArr[i]);
            for (int j = f; j <= i - 1; j++) {
                dparr[j] = min(dparr[j], dparr[i] + 1);
            }
        }
        return dparr[u];
    };
    i64 ans = 0;
    int i   = n - 1;
    while (i > 0 && aArr[i] == 0) {
        i--;
    }
    for (; i > 0;) {
        int j = i - 1;
        while (j > 0 && aArr[j] == 0) {
            j--;
        }
        if (j >= i - cArr[i]) {
            ans++;
        } else {
            ans += dp(j, i);
        }
        i = j;
    }
    cout << ans << '\n';
    return 0;
}