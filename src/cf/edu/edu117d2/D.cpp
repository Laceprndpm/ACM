#include <iostream>
#include <utility>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 a, b, x;
    cin >> a >> b >> x;
    if (a > b) swap(a, b);
    bool flag = false;
    if (a == x || b == x) flag = true;
    while (b > x && a != 0) {
        i64 next_b = b % a;
        if (next_b <= x) {
            if (x % a == next_b) {
                flag |= true;
            }
        }
        b = next_b;
        swap(a, b);
    }
    cout << (flag ? "Yes\n" : "No\n");
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