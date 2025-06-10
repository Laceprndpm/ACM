#include <array>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> drr(n);
    for (int i = 0; i < n; i++) {
        cin >> drr[i];
    }
    vector<array<int, 2>> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i][0] >> arr[i][1];
    }
    int         l = 0, r = 0;
    bool        ok = 1;
    vector<int> arrL(n + 1);
    for (int i = 0; i < n; i++) {
        if (drr[i] == -1) {
            r++;
        } else if (drr[i] == 1) {
            l++, r++;
        }
        if (l > arr[i][1] || r < arr[i][0]) {
            ok = false;
        }
        l           = max(l, arr[i][0]);
        r           = min(r, arr[i][1]);
        arrL[i + 1] = l;
    }
    if (ok) {
        int cur = arrL[n];
        for (int i = n - 1; i >= 0; i--) {
            if (drr[i] == 1) {
                cur--;
            } else if (drr[i] == 0) {
                continue;
            } else {
                if (cur > arrL[i]) {
                    drr[i] = 1;
                    cur--;
                } else {
                    drr[i] = 0;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            cout << drr[i] << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
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