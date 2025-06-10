#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n, k;
    cin >> n >> k;
    string flag;
    cin >> flag;
    vector<i64> val(n);
    int         theOne = -1;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
        if (flag[i] == '0') {
            val[i] = -(i64)1e18 + 1;
            if (theOne == -1) {
                theOne = i;
            }
        }
    }
    vector<i64> prefix(1 + n);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = max(prefix[i] + val[i], 0ll);
    }
    vector<i64> suffix(1 + n);
    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = max(suffix[i + 1] + val[i], 0ll);
    }
    if (*max_element(prefix.begin(), prefix.end()) > k) {
        cout << "No\n";
        return;
    }
    if (theOne == -1 && *max_element(prefix.begin(), prefix.end()) != k) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    if (theOne != -1) val[theOne] = k - prefix[theOne] - suffix[theOne + 1];
    for (int i = 0; i < n; i++) {
        cout << val[i] << ' ';
    }
    cout << '\n';
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
    // 如果我用-1e18补全所有空，那么我就可以在所有非空上dp求得mx，并且找到某一个幸运儿，将他通过修改来得到mx
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}