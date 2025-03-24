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
    // 1 2 4 8
    // 3 6
    // 5
    // 选择2一定是最优的吗？试试看吧
    cout << 2 << '\n';
    vector<bool> done(n + 1);
    for (int i = 1; i <= n; i++) {
        if (!done[i]) {
            for (int j = i; j <= n; j *= 2) {
                cout << j << ' ';
                done[j] = true;
            }
        }
    }
    cout << '\n';
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