#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int    r, x;
    string Y = "Yes\n", N = "No\n";
    cin >> r >> x;
    if (x == 1) {
        cout << ((r <= 2999 && r >= 1600) ? Y : N);
    } else {
        cout << ((r <= 2399 && r >= 1200) ? Y : N);
    }
    return 0;
}