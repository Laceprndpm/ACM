#include <bits/stdc++.h>
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
    if (n % 2 != 0) {
        cout << -1 << '\n';
        return;
    }
    stack<int>  regular;
    stack<int>  irregular;
    vector<int> ans(n);
    bool        isRegular   = false;
    bool        isIrregular = false;
    try {
        for (int i = 0; i < n; i++) {
            char cur = s[i];
            if (cur == '(') {
                if (!irregular.empty()) {
                    irregular.pop();
                    ans[i] = 2;
                } else {
                    regular.push(1);
                    ans[i]    = 1;
                    isRegular = true;
                }
            } else {
                if (!regular.empty()) {
                    regular.pop();
                    ans[i] = 1;
                } else {
                    irregular.push(1);
                    ans[i]      = 2;
                    isIrregular = true;
                }
            }
        }
    } catch (const exception& e) {
        cout << -1 << '\n';
        return;
    }
    if (!regular.empty() || !irregular.empty()) {
        cout << -1 << '\n';
        return;
    }
    cout << isIrregular + isRegular << '\n';
    if (isIrregular + isRegular == 1) {
        for (int i = 0; i < n; i++) {
            cout << 1 << ' ';
        }
    } else {
        for (int i = 0; i < n; i++) {
            cout << ans[i] << ' ';
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