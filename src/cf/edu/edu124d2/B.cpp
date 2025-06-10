#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

i64 qpow(i64 n, i64 q)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
        }
        n *= n;
        q >>= 1;
    }
    return ans;
}

void solve()
{
    int n;
    cin >> n;
    if (n > 19) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        cout << qpow(3ll, i) << ' ';
    }
    cout << '\n';
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
    // a + b <= 2 * (a - b)
    //   3*b <= a
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}