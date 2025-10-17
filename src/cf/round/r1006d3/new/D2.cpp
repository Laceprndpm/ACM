#include <iostream>
#include <set>
#include <vector>

using namespace std;

using i64 = long long;
// E
void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    auto check = [&](int k) {
        multiset<int> st(arr.begin(), arr.end());
        for (int i = k; i >= 1; i--) {
            auto it = st.upper_bound(i);
            if (it == st.begin()) {
                return false;
            }
            it--;
            st.erase(it);

            if (!st.empty()) {
                it = st.begin();
                st.erase(it);
            }
        }
        return true;
    };

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!check(i)) {
            break;
        }
        ans = i;
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
