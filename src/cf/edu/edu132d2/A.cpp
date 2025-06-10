#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int x;
    cin >> x;
    vector<int>a(4);
    cin >> a[1] >> a[2] >> a[3];
    if (a[x] == 0) {
        cout << "No\n";
        return;
    }
    for (int i = 1; i <= 3; i++) {
        if (a[i] == i) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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