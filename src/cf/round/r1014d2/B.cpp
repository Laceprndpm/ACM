#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            if (a[i] == '0') {
                cnt1++;
            }
            if (b[i] == '0') {
                cnt2++;
            }
        } else {
            if (a[i] == '0') {
                cnt2++;
            }
            if (b[i] == '0') {
                cnt1++;
            }
        }
    }
    if (cnt1 < (n + 1) / 2) {
        cout << "No\n";
        return;
    }
    if (cnt2 < n / 2) {
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