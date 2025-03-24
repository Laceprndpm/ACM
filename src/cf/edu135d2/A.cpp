#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int maxn = 0;
    int n;
    int maxidx = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        if (cur > maxn) {
            maxn = cur;
            maxidx = i;
        }
    }
    cout << maxidx << '\n';
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