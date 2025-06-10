#include <algorithm>
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
        if (count(s.begin(), s.end(), '2') <= 2 && count(s.begin(), s.end(), '2') != 0) {
            cout << "No\n";
            continue;
        }
        auto frist = find(s.begin(), s.end(), '2') - s.begin();
        auto last  = n - (find(s.rbegin(), s.rend(), '2') - s.rbegin()) - 1;
        cout << "Yes\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    cout << 'X';
                    continue;
                }
                if (s[i] == '1' || s[j] == '1') {
                    cout << '=';
                } else {
                    if (i == frist && j == last) {
                        cout << '-';
                        continue;
                    }
                    if (i == last && j == frist) {
                        cout << '+';
                        continue;
                    }
                    if (i < j) {
                        cout << '+';
                    } else {
                        cout << '-';
                    }
                }
            }
            cout << '\n';
        }
    }
    return 0;
}