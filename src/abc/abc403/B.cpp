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
    string s, ss;
    cin >> s >> ss;
    int lenS  = s.length();
    int lenSS = ss.length();
    for (int i = 0; i <= lenS - lenSS; i++) {
        bool flag = 1;
        for (int j = 0; j < lenSS; j++) {
            if (s[i + j] != ss[j] && s[i + j] != '?') {
                flag = 0;
                break;
            }
        }
        if (flag) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}