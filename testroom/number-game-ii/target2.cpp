#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
// vectors
#define bg(x)  begin(x)
#define all(x) bg(x), end(x)

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(all(arr));
    auto check = [&](int k) {
        int ptr2 = upper_bound(all(arr), k) - arr.begin();
        if (ptr2 == n) {
            ptr2--;
        }
        int ptr1 = 0;
        for (int i = k; i >= 2; i--) {
            while (ptr2 >= 0 && arr[ptr2] > i) {
                ptr2--;
            }
            if (ptr2 < ptr1) return false;
            if (arr[ptr2] > k) return false;
            ptr2--;
            ptr1++;
        }
        while (ptr2 >= 0 && arr[ptr2] > 1) {
            ptr2--;
        }
        if (ptr2 - ptr1 < 0) return false;
        if (arr[ptr2] > 1) return false;
        return true;
    };

    int ans = 0;
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l   = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << '\n';
}

signed main(signed argc, char** argv)
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
