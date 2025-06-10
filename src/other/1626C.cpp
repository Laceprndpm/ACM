#include <iostream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    stack<pair<i64, i64>> st;
    int                   n;
    cin >> n;
    vector<i64> karr(n);
    vector<i64> harr(n);
    for (int i = 0; i < n; i++) {
        cin >> karr[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> harr[i];
    }
    for (int i = 0; i < n; i++) {
        int l = karr[i] - harr[i] + 1;
        int r = karr[i];
        while (!st.empty() && st.top().first > l) {
            st.pop();
        }
        if (st.empty() || st.top().second < l) {
            st.push({l, r});
        } else {
            st.top() = {st.top().first, r};
        }
    }
    i64 ans = 0;
    while (!st.empty()) {
        ans += (st.top().second - st.top().first + 2) * (st.top().second - st.top().first + 1) / 2;
        st.pop();
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
    // 每个连续块间如果相隔2，那么就完全无关？相隔3才能完全无关
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

