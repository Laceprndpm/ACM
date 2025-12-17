#include <algorithm>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n;
    cin >> n;
    string s;
    cin >> s;
    i64 cntD   = count(s.begin(), s.end(), 'D');
    i64 cntR   = count(s.begin(), s.end(), 'R');
    i64 emptyB = 0;
    if (s[0] == 'R') {
        auto firstD = find(s.begin(), s.end(), 'D');
        if (firstD == s.end()) {
            cout << n << '\n';
            return;
        } else {
            i64 alreadyR = firstD - s.begin();
            emptyB       = (n - 1) * (firstD - s.begin());
            auto nextR   = find(firstD, s.end(), 'R');
            if (nextR == s.end()) {
                cout << n * n - emptyB << '\n';
                return;
            } else {
                // int alreadyD = nextR - firstD;
                emptyB += (cntD) * (cntR - alreadyR);
                cout << n * n - emptyB << '\n';
                return;
            }
        }
    } else {
        auto firstR = find(s.begin(), s.end(), 'R');
        if (firstR == s.end()) {
            cout << n << '\n';
            return;
        } else {
            i64 alreadyD = firstR - s.begin();
            emptyB       = (n - 1) * (firstR - s.begin());
            auto nextD   = find(firstR, s.end(), 'D');
            if (nextD == s.end()) {
                cout << n * n - emptyB << '\n';
                return;
            } else {
                // int alreadyR = nextD - firstR;
                emptyB += (cntR) * (cntD - alreadyD);
                cout << n * n - emptyB << '\n';
                return;
            }
        }
    }
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
