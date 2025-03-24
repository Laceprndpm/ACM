#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        tmp--;
        tmp %= k;
        // 模k后的血量
        // 1 2 3 4 k = 4 3 2 1
        //
        tmp           = k - tmp;
        arr[i].first  = tmp;
        arr[i].second = i + 1;
    }

    stable_sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) {
        cout << arr[i].second << ' ';
    }
    cout << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}