#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    // 如果能取得k名，那么就
    // 1.战胜原本的第k名，即n - k + 1，并且胜利至少n - k场
    // 2.输掉原本k名，但赢得n - k + 1场
    vector<int> sortedarr(arr);
    sort(sortedarr.begin() + 1, sortedarr.end(), less<int>());
    vector<int> prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + sortedarr[i];
    }
    function<bool(int k)> check = [&](int k) {
        if (prefix[n - k + 1] <= m) {  // 如果能战胜n - k + 1个
            return true;
        }

        if (prefix[n - k] <= m) {  // n - k 个，如果在此基础上可以战胜第k名
            if (arr[n - k + 1] <= sortedarr[n - k]) {
                return true;
            } else if (m - prefix[n - k] + sortedarr[n - k] >= arr[n - k + 1]) {
                return true;
            }
        }
        return false;
    };
    int l = n + 1, r = 1;
    while (l > r) {
        int mid = (r + l) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid + 1;
        }
    }
    cout << l << '\n';
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