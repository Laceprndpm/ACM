#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

// retry 2025-03-08
signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[i] == 0 && i + 1 <= n && arr[i + 1] != 0) {
            bool doubA = false;
            i++;
            while (i <= n && arr[i] != 0) {
                if (arr[i] == 2) {
                    doubA = true;
                }
                i++;
            }
            cnt++;
            if (!doubA) {
                i--;
            }
            continue;
        }
        if (arr[i] == 0) {
            cnt++;
            continue;
        }
        if (arr[i] != 0) {
            while (i <= n && arr[i] != 0) {
                i++;
            }
            cnt++;
            continue;
        }
    }
    cout << cnt << '\n';
    return 0;
}