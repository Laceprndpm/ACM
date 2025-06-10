#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = 0;
    int remain;
    for (int i = 0; i < n; i++) {
        if (s[i] == s[i + 1]) {
            i += 1;
            cnt++;
            continue;
        }
        if (s[i] == '(' && s[i + 1] == ')') {
            i += 1;
            cnt++;
            continue;
        }
        int  p    = i;
        bool flag = false;
        for (int j = i + 2; j < n; j++) {
            if (s[j] == ')') {
                i    = j;
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << cnt << ' ' << n - p << '\n';
            return;
        } else {
            cnt++;
        }
    }
    cout << cnt << ' ' << 0 << '\n';
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