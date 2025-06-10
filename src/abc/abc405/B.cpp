#include <iostream>
#include <set>
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
    int n, m;
    cin >> n >> m;
    set<int> st;
    for (int i = 1; i <= m; i++) {
        st.insert(i);
    }
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        if (st.count(cur) != 0) {
            st.erase(cur);
            if (st.empty()) {
                cout << n - i << '\n';
                return 0;
            }
        }
    }
    cout << 0 << '\n';
    return 0;
}