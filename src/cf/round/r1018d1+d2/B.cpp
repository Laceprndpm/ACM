#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <ratio>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    // 最后的样子应该是，取了k-1对手套，加一个一半和1，并且剩下的n - k全部取一半
    i64 n, k;
    cin >> n >> k;
    vector<i64> leftS(n), rightS(n);
    for (int i = 0; i < n; i++) {
        cin >> leftS[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> rightS[i];
        if (rightS[i] > leftS[i]) {
            swap(rightS[i], leftS[i]);
        }
    }
    i64 ans = accumulate(leftS.begin(), leftS.end(), 0ll);
    sort(rightS.begin(), rightS.end(), greater<>());
    ans += accumulate(rightS.begin(), rightS.begin() + k - 1, 0ll) + 1;
    cout << ans << '\n';
}

signed main(int argc, char** argv)
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