#include <bits/stdc++.h>
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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n >= 5 || n == 1) {
            cout << "Alice" << '\n';
        } else {
            cout << "Bob" << '\n';
        }
    }
    return 0;
}

// n == 2, bob
// n = 3,bob
// n == 4,BOB
// 1 1 1 1
// 2 1 1 | 3 1
// 2 2
// 4
// 1 1 1 1 1
// if n >= 5
// Alice选择n-2个，那么Bob只能