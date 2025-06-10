#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int x1 = -1e8, y1 = -1e8;
    int k;
    cin >> k;
    vector<pair<int, int>> points;
    while (k) {
        int cnt = 2;
        int cur = 2;  // 组合数,cur = cnt : 2
        for (int i = 3; cur * i / 2 / (i - 2) <= k; i++) {
            cnt++;
            cur *= i;
            cur /= i - 2;
        }
        k -= cur / 2;
        for (int i = 0; i < cnt; i++) {
            points.emplace_back(x1, y1);
            x1++;
        }
        x1++;
        y1++;
    }
    cout << points.size() << '\n';
    for (auto i : points) {
        cout << i.first << ' ' << i.second;
        cout << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}