#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1);
    vector<int> pos2val(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        pos2val[arr[i]] = i;
    }
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        if (pos2val[k] < l || pos2val[k] > r || l > r) {
            cout << "-1 ";
            continue;
        }
        int tgt  = pos2val[k];
        int cntS = 0, cntB = 0;
        int curS = 0, curB = 0;
        while (true) {
            int mid = (r + l) / 2;
            if (mid == tgt) {
                break;
            }
            if (mid < tgt) {
                if (arr[mid] > k) {
                    cntS++;
                } else {
                    curS++;
                }
                l = mid + 1;
            } else {
                if (arr[mid] < k) {
                    cntB++;
                } else {
                    curB++;
                }
                r = mid - 1;
            }
        }
        if (cntS + curS > k - 1 || cntB + curB > n - k) {
            cout << "-1 ";
            continue;
        }
        cout << abs(cntB - cntS) + cntB + cntS << ' ';
    }
    cout << '\n';
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