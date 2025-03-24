#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> arr;
    int                    minj = m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'R') {
                arr.emplace_back(i, j);
                minj = min(minj, j);
            }
        }
    }
    sort(arr.begin(), arr.end(), less<>());
    if (arr.empty()) {
        cout << "No\n";
        return;
    } else if (arr[0].second != minj) {
        cout << "No\n";
        return;
    } else {
        cout << "Yes\n";
        return;
    }
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