#include <bits/stdc++.h>
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
    int k;
    cin >> k;
    int r = 1 << k;
    r--;
    vector<int> arr(r);
    for (int i = 0; i < r; i++) {
        cin >> arr[i];
    }
    i64 ans = 1;
    while (k--) {
        int curR = 1 << k;
        curR--;
        vector<int> nArr(curR / 2);
        for (int i = 0; i < curR / 2; i += 2) {
            int mx = max(arr[2 * i], arr[2 * i + 1]);
            int mn = min(arr[2 * i], arr[2 * i + 1]);
            if (mn > (1 << k)) {
                cout << 0 << '\n';
                return 0;
            }
            if (mn == -1) {
                nArr[i] = mx;
            }
        }
    }
    return 0;
}