#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

// 很明显只有两种情况，一是头尾相同，二是有两个相同的连续子串
void solve()
{
    string s1;
    string s2;
    cin >> s1;
    cin >> s2;
    if (s1[0] == s2[0]) {
        cout << "YES\n";
        cout << s1[0] << '*' << '\n';
        return;
    } else if (s1.back() == s2.back()) {
        cout << "YES\n";
        cout << '*' << s1.back() << '\n';
        return;
    }
    for (int i = 0; i < s1.length() - 1; i++) {
        for (int j = 0; j < s2.length() - 1; j++) {
            if (s1[i] == s2[j] && s1[i + 1] == s2[j + 1]) {
                cout << "YES\n";
                cout << '*' << s1[i] << s1[i + 1] << '*' << '\n';
                return;
            }
        }
    }
    cout << "NO\n";
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