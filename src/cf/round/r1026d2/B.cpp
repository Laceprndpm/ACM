#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    int n   = s.length();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            cnt++;
        } else {
            cnt--;
            if (i != n - 1 && cnt == 0) {
                cout << "Yes\n";
                return;
            }
        }
    }
    cout << "No\n";
    return;
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