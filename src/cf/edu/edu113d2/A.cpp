#include <iostream>
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
        string s;
        cin >> s;
        int f = false;
        for (int i = 0; i < n - 1; i++) {
            if (s[i] != s[i + 1]) {
                cout << i + 1 << ' ' << i + 2 << '\n';
                f = true;
                break;
            }
        }
        if (!f) cout << "-1 -1\n";
    }
    return 0;
}