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
    // 1010
    // 必须有都为1的，不然a+b=c了
    // 可以保证
    // x+y>z
    // 如何避免
    // y + z <= x?
    // 有一个x为0，y为1即可
    // 1010 11
    bool has1 = false, has0 = false;
    int  y = 0;
    for (int i = 0; (x >> i) != 0; i++) {
        if (((x >> i) & 1) == 0 && !has0) {
            has0 = true;
            y += 1 << i;
        }
        if (((x >> i) & 1) == 1 && !has1) {
            y += 1 << i;
            has1 = true;
        }
    }
    if (!has0 || !has1 || y >= x) {
        cout << -1 << '\n';
        return;
    }
    cout << y << '\n';
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