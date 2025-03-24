#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int x, n, m;
    cin >> x >> n >> m;
    if (n + m >= 32) {
        cout << 0 << ' ' << 0 << '\n';
        return;
    }
    int x1 = x;
    int n1 = n, m1 = m;
    while (n1 + m1) {
        if (n1 && x1 % 2) {
            x1 /= 2;
            n1--;
        } else {
            x1++;
            x1 /= 2;
            m1--;
        }
    }
    n1 = n, m1 = m;
    int x2 = x;
    while (n1 + m1) {
        if (n1 && x2 % 2 == 0) {
            x2 /= 2;
            n1--;
        } else {
            x2++;
            x2 /= 2;
            m1--;
        }
    }
    cout << x2 << ' ' << x1 << '\n';
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