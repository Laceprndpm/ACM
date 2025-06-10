#include <array>
#include <ios>
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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = '0' + s;
    vector<array<i64, 26>> ac(n + 1);
    vector<i64>            last(26, -1);
    for (int i = n; i >= 0; i--) {
        int curC = s[i] - 'a';
        for (int j = 0; j < k; j++) {
            ac[i][j] = last[j];
        }
        last[curC] = i;
    }
    vector<i64> dp(n + 1, 1);
    for (int i = n; i >= 0; i--) {
        i64  mx   = 0;
        bool last = false;
        for (int j = 0; j < k; j++) {
            if (ac[i][j] != -1)
                mx = max(ac[i][j], mx);
            else
                last = true;
        }
        if (!last)
            dp[i] = dp[mx] + 1;
        else
            dp[i] = 1;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string qs;
        cin >> qs;
        int lenqs = qs.length();
        int o     = 0;
        for (int j = 0; j < lenqs; j++) {
            int curC = qs[j] - 'a';
            o        = ac[o][curC];
            if (o == -1) {
                break;
            }
        }
        if (o == -1) {
            cout << 0 << '\n';
        } else {
            cout << dp[o] << '\n';
        }
    }
    return 0;
}