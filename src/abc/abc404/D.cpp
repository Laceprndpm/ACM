#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr i64 INF = 1e16;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<i64>         cArr(n + 1);
    vector<vector<int>> lis(n + 1);
    vector<int>         vist(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cArr[i];
    }
    for (int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        for (int j = 1; j <= k; j++) {
            int na;
            cin >> na;
            lis[na].push_back(i);
        }
    }
    int b = 1;
    for (int i = 0; i <= n; i++) {
        b *= 3;
    }
    b--;
    i64 ans = INF;
    for (int b3 = 0; b3 <= b; b3++) {
        int cur = b3;
        vist.assign(m + 1, 0);
        i64 mon = 0;
        for (int i = 1; i <= n; i++) {
            i64 t = cur % 3;
            for (int v : lis[i]) {
                vist[v] += t;
            }
            mon += cArr[i] * t;
            cur /= 3;
        }
        bool flag = true;
        for (int i = 1; i <= m; i++) {
            if (vist[i] < 2) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ans = min(ans, mon);
        }
    }
    cout << ans << '\n';
    return 0;
}