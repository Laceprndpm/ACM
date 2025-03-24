#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    // vector<int> appear(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<int> prefix(n + 1);
    // for (int i = 1; i <= n; i++) {
    //     prefix[i] = prefix[i - 1] + appear[i];
    // }
    sort(arr.begin(), arr.end());
    int l = 0;
    int r = (n + 1) / 2;

    function<bool(int x)> check = [&](int k) {
        multiset<int> st;
        for (int i = 1; i <= n; i++)
            st.insert(arr[i]);
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

    while (l < r) {
        int mid = (l + r) / 2 + 1;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
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
    // 1 1 2
    // 1 1
    // 3 1
    // 3

    //
    // alice和bob轮流删除元素，alice需要删除<=k,<=k-1,<=k-2...<=1
    // 如过<=k的元素为2*k-1个，就可以？
    // 不对，应该是对于k之前的元素，全部满足<=k的
    // 如果bob提前删除了所有1，那么alice无法胜利
    // 假如最大k次
    // 那么至少有k-1个<=1，k-2个<=2...
    //
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}