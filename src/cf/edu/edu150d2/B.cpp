#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int q;
    cin >> q;
    int firstElement;
    cin >> firstElement;
    cout << 1;
    int last = firstElement;
    int cur  = 1;
    for (; cur < q; cur++) {
        int curElement;
        cin >> curElement;
        if (curElement >= last) {
            cout << 1;
            last = curElement;
        } else if (curElement <= firstElement) {
            last = curElement;
            cout << 1;
            cur++;
            break;
        } else {
            cout << 0;
        }
    }
    for (; cur < q; cur++) {
        int curElement;
        cin >> curElement;
        if (curElement <= firstElement && curElement >= last) {
            last = curElement;
            cout << 1;
        } else {
            cout << 0;
        }
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}