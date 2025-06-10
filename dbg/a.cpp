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
    string s;
    cin >> s;
    int n        = s.size();
    int last     = -1;
    int lastlast = -1;
    i64 ans      = 0;
    for (int i = 0; i < n; i++) {
        if (i && s[i - 1] != s[i] && s[i - 1] + 1 != s[i]) {
            lastlast = last;
            last     = i - 1;
        }
        ans += i - lastlast;
    }
    cout << ans << '\n';
    return 0;
}