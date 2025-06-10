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
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    set<int> st;
    for (int i = 1; i <= n; i++) {
        st.insert(i);
    }
    vector<int> prefix(n + 1);
    vector<int> suffix(n + 1);
    int         cur = 0;
    for (int i = 1; i <= n; i++) {
        auto it = st.upper_bound(arr[i]);
        if (it == st.begin()) continue;
        cur++;
        prefix[cur] = i;
        st.erase(--it);
    }
    for (int i = 1; i <= n; i++) {
        st.insert(i);
    }
    cur = 0;
    for (int i = n; i >= 1; i--) {
        auto it = st.upper_bound(arr[i]);
        if (it == st.begin()) continue;
        cur++;
        suffix[cur] = i;
        st.erase(--it);
    }
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        if (prefix[i] > suffix[i]) {
            break;
        }
        ans += suffix[i] - prefix[i];
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