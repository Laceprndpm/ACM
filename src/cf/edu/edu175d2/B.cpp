#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = INT32_MAX;

void solve()
{
    i64 n, x, k;
    cin >> n >> x >> k;
    string s;
    cin >> s;
    int cur     = 0;
    int frist0  = -1;
    int fristNx = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'L') {
            cur--;
        } else {
            cur++;
        }

        if (cur == 0 && frist0 == -1) {
            frist0 = i + 1;
        }
        if (cur == -x && fristNx == -1) {
            fristNx = i + 1;
        }
    }
    if (fristNx == -1) {
        cout << 0 << '\n';
        return;
    }
    if (k < fristNx) {
        cout << 0 << '\n';
        return;
    } else {
        if (frist0 != -1) {
            k -= fristNx;
            i64 ans = k / frist0 + 1;
            cout << ans << '\n';
        } else {
            cout << 1 << '\n';
        }
    }
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