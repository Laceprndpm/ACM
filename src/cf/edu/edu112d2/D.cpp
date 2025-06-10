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
    // abcabcabc
    // 必须是abcabc三元循环序
    // 算上偏移量，一共有3 * 2种情况，可接受
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<vector<int>> arr(6, vector<int>(n + 1));
    for (int i = 0; i < 3; i++) {
        string tmp = "abc";
        for (int j = 0; j < n; j++) {
            arr[i][j + 1] += arr[i][j] + (s[j] != tmp[(j + i) % 3]);
        }
    }
    for (int i = 3; i < 6; i++) {
        string tmp = "acb";
        for (int j = 0; j < n; j++) {
            arr[i][j + 1] += arr[i][j] + (s[j] != tmp[(j + i) % 3]);
        }
    }
    for (int i = 0; i < m; i++) {
        int ans = INF;
        int l, r;
        cin >> l >> r;
        for (int j = 0; j < 6; j++) {
            ans = min(ans, arr[j][r] - arr[j][l - 1]);
        }
        cout << ans << '\n';
    }
    return 0;
}