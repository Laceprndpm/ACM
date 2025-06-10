#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> ai(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> ai[i];
    }
    int m;
    cin >> m;
    vector<int> bi(m + 1);
    i64         sum = 0;
    for (int i = 1; i <= m; i++) {
        cin >> bi[i];
        sum += bi[i];
        sum %= n;
    }
    cout << ai[sum] << '\n';
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