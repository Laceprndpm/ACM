#include <algorithm>
#include <cwchar>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> bd(n, vector<int>(m));
    for (auto& i : bd) {
        for (int& j : i) {
            cin >> j;
        }
    }
    vector<vector<i64>> prefix(n, vector<i64>(m + 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            prefix[i][j + 1] += prefix[i][j] + bd[i][j];
        }
    }
    for (int j = 1; j < m; j++) {  // 分界
        vector<int>        a;
        vector<int>        b;
        int                topa    = 0;
        int                topb    = 0;
        function<i64(int)> leftval = [&](int u) -> i64 {
            return prefix[u][j];
        };
        function<i64(int)> rightval = [&](int u) -> i64 {
            return prefix[u][m] - prefix[u][j];
        };
        i64 left  = 0;
        i64 right = 0;
        for (int i = 0; i < n; i++) {
            if (leftval(i) >= rightval(i)) {
                a.emplace_back(i);
                left += leftval(i);
                right -= rightval(i);
            } else {
                b.emplace_back(i);
                left -= leftval(i);
                right += rightval(i);
            }
        }
        sort(a.begin(), a.end(), [&](int u, int v) {
            return leftval(u) - rightval(u) < leftval(v) - rightval(v);
        });
        sort(b.begin(), b.end(), [&](int u, int v) {
            return leftval(u) - rightval(u) > leftval(v) - rightval(v);
        });
        if (left < 0) {
            while (left <= 0 && topb < (int)b.size() - 1) {
                left += leftval(b[topb++]);
                right -= rightval(b[topb]);
                a.push_back(b[topb]);
            }
        } else {
            while (right <= 0 && topa < (int)a.size() - 1) {
                right += rightval(a[topa++]);
                left -= leftval(a[topa]);
                b.push_back(a[topa]);
            }
        }
        // 每行，假如涂红就是加左减右
        // 涂蓝反之
        // 假如存在一种涂色方案，使得其成立，且i为蓝
        // 那么假如存在left[i] > left[j] && right[j] < right[j]
        // 或者默认
        //
        if (left > 0 && right > 0) {
            cout << "Yes\n";
            string result(n, 'B');
            for (int ta = topa; ta < (int)a.size(); ta++) {
                result[ta] = 'R';
            }
            cout << result << ' ' << j << '\n';
            return;
        }
    }
    cout << "No\n";
    return;
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