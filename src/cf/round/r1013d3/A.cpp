#include <vector>
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
    int cnt0 = 3;
    int cnt1 = 1;
    int cnt2 = 2;
    int cnt3 = 1;
    int cnt5 = 1;
    int ok   = 5;

    int ans = 0;
    for (int j = 1, i; j <= n; j++) {
        cin >> i;
        if (i == 0 && cnt0) {
            cnt0--;
            if (cnt0 == 0) {
                ok--;
            }
        }
        if (i == 1 && cnt1) {
            cnt1--;
            if (cnt1 == 0) {
                ok--;
            }
        }
        if (i == 2 && cnt2) {
            cnt2--;
            if (cnt2 == 0) {
                ok--;
            }
        }
        if (i == 3 && cnt3) {
            cnt3--;
            if (cnt3 == 0) {
                ok--;
            }
        }
        if (i == 5 && cnt5) {
            cnt5--;
            if (cnt5 == 0) {
                ok--;
            }
        }
        if (ok == 0) {
            ans = j;
            ok  = -1;
        }
    }
    cout << ans << '\n';
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