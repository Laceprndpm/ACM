#include <bits/stdc++.h>
using namespace std;
using i64              = long long;
using PII              = pair<int, int>;
using Graph            = vector<vector<int>>;
constexpr int      INF = INT32_MAX;
unordered_set<int> badapple{1, 8, 49, 288, 1681, 9800, 57121, 332928};

void solve()
{
    int n;
    cin >> n;
    if (badapple.count(n) != 0) {
        cout << "-1" << '\n';
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (badapple.count(i) != 0) {
            cout << i + 1 << ' ' << i << ' ';
            i++;
        } else {
            cout << i << ' ';
        }
    }
    cout << '\n';
}

// 1
// 2 1 3 4 5 6 7
//
//
// (1 + n) * n / 2 != k ^ 2
//
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