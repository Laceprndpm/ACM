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
    if (n >= 3) {
        // 如果为偶数，那么一定以0结尾
        if (n % 2 == 0) {
            for (int i = n - 2; i >= 1; i--) {
                cout << i << ' ';
            }
            cout << n - 1 << ' ' << n << '\n';
            return;
        } else {
            cout << 1 << ' ';
            for (int i = n - 2; i >= 2; i--) {
                cout << i << ' ';
            }
            cout << n - 1 << ' ' << n << '\n';
            return;
        }
    }
    if (n == 2) {
        cout << 1 << ' ' << 2 << '\n';
        return;
    }
    cout << 1 << '\n';
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