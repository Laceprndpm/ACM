#include <algorithm>
#include <cctype>
#include <cstdio>
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
    vector<int> row(n + 1);
    vector<int> col(m + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char temp;
            while ((temp = getchar()) && !isdigit(temp)) {
            }
            temp -= '0';
            row[i] ^= temp;
            col[j] ^= temp;
        }
    }
    int row1 = count(row.begin() + 1, row.end(), 1);
    int col1 = count(col.begin() + 1, col.end(), 1);
    int ans  = max(row1, col1);
    cout << ans << '\n';
}

signed main(int argc, char** argv)
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
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