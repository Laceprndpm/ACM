#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    int last = -1;
    int cnt  = 0;
    int pos1 = -1, pos2 = -1;
    int len = s.length();
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == ')') {
            if (last == 1) {
                cnt++;
                if (cnt > 2) {
                    cout << "No\n";
                    return;
                }
                if (pos1 == -1) {
                    pos1 = i;
                } else {
                    pos2 = i;
                }
            }
            last = 1;
        }
        if (c == '[' || c == ']') {
            if (last == 0) {
                cnt++;
                if (cnt > 2) {
                    cout << "No\n";
                    return;
                }
                if (pos1 == -1) {
                    pos1 = i;
                } else {
                    pos2 = i;
                }
            }
            last = 0;
        }
    }
    cout << "Yes\n";
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
    int n;
    cin >> n;
    while (n--) {
        solve();
    }
    return 0;
}