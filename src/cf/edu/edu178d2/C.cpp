#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
#define B "Bob\n"
#define A "Alice\n"

void solve()
{
    int n;
    cin >> n;
    string card;
    cin >> card;
    if (card[0] == 'B') {
        if (card[n - 1] == 'B' || card[n - 2] == 'B') {
            cout << B;
        } else {
            cout << A;
        }
    } else {
        if (card[n - 1] == 'A') {
            cout << A;
        } else {
            int cntB = 0;
            for (char c : card) {
                if (c == 'B') {
                    cntB++;
                }
            }
            if (cntB == 1) {
                cout << A;
            } else {
                cout << B;
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