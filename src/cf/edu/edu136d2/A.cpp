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
    if (n > 1) {
        cout << 2 << ' ';
    } else {
        cout << 1 << ' ';
    }
    if (m > 1) {
        cout << 2 << ' ';
    } else {
        cout << 1 << ' ';
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