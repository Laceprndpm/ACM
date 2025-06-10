#include <set>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string    s;
    set<char> st;
    cin >> s;
    for (char i : s) {
        st.insert(i);
    }
    cin >> s;
    for (char i : s) {
        st.insert(i);
    }
    if (st.size() == 2) {
        cout << 1 << '\n';
    }
    if (st.size() == 1) {
        cout << 0 << '\n';
    }
    if (st.size() == 3) {
        cout << 2 << '\n';
    }
    if (st.size() == 4) {
        cout << 3 << '\n';
    }
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