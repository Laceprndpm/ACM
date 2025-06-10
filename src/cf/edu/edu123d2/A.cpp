#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    bool r = false, g = false, b = false;
    for (char i : s) {
        switch (i) {
            case 'r':
                r = true;
                break;
            case 'g':
                g = true;
                break;
            case 'b':
                b = true;
                break;
            case 'R':
                if (!r) {
                    cout << "NO\n";
                    return;
                }
                break;
            case 'G':
                if (!g) {
                    cout << "NO\n";
                    return;
                }
                break;
            case 'B':
                if (!b) {
                    cout << "NO\n";
                    return;
                }
                break;
        }
    }
    cout << "YES\n";
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