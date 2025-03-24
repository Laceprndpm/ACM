#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    if (k % 2)
        for (int i = 1; i <= n - 2; i++) {
            cout << n << ' ';
        }
    else
        for (int i = 1; i <= n - 2; i++) {
            cout << n - 1 << ' ';
        }
    cout << n << ' ' << n - 1 << '\n';
}

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