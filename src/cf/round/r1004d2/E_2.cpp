#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<i64> arr(n);
    vector<i64> zero;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] == 0) {
            zero.push_back(i);
        }
    }
    if (zero.size() == 0) {
        cout << n << '\n';
        return;
    }
    vector<i64> prefixMin(n + 1), suffixMEX(n + 1);
    prefixMin[0] = INF;
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) prefixMin[i + 1] = min(prefixMin[i], arr[i]);
    }
    set<i64> st;
    for (int i = 0; i <= n; i++) {
        st.insert(i);
    }
    for (int i = n - 1; i >= 0; i--) {
        if (st.count(arr[i]) != 0) st.erase(arr[i]);
        suffixMEX[i] = *st.begin();
    }
    bool flag = true;
    for (int i = 1; i < n; i++) {
        if (i - 1 == zero[0]) break;
        if (prefixMin[i] < suffixMEX[i]) {
            flag = false;
            break;
        }
    }
    i64 ans = n - zero.size();
    if (flag) {
        ans++;
    }
    cout << ans << '\n';
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