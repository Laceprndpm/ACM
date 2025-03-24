#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    // problem A
    string s;
    cin >> s;
    char p   = 0;
    int  cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == p) {
            cnt++;
        } else {
            if (cnt == 1) {
                cout << "No\n";
                return;
            }
            cnt = 1;
            p   = s[i];
        }
    }
    if (cnt == 1) {  // 尾判
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
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