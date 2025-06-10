#include <cctype>
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
    int q;
    cin >> q;
    // 1 | 0 | 0 1 | 0 1 1 0 | 0 1  1  0  1  0  0  1
    // 0   1   2 3   4 5 6 7   8 9  10 11 12 13 14 15
    int n = s.length();
    while (q--) {
        i64 x;
        cin >> x;
        x--;
        i64 idx1 = (x) / n;
        x %= n;
        int cnt1 = 0;
        for (i64 i = 60; i >= 0; i--) {
            if (idx1 >> i & 1) {
                cnt1++;
            }
        }
        if (cnt1 % 2 == 0) {
            cout << s[x] << ' ';
        } else {
            if (isupper(s[x])) {
                cout << (char)tolower(s[x]) << ' ';
            } else {
                cout << (char)toupper(s[x]) << ' ';
            }
        }
    }
    return 0;
}