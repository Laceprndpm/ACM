#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n;
    cin >> n;
    string s;
    cin >> s;
    i64         maxn = 0;
    vector<i64> up(n + 1), down(n + 1);
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            up[i + 1] += up[i] + i;
            down[i + 1] += down[i] + n - i - 1ll;
            maxn = max<i64>({maxn, up[i + 1], down[i + 1]});
        } else {
            up[i + 1] += down[i] + 1ll;
            maxn = max<i64>({maxn, up[i + 1]});
        }
    }
    cout << maxn << '\n';
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