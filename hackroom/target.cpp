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
    i64 L, R;
    cin >> L >> R;
    set<i64> st;
    for (i64 i = 0; i <= 62; i++) {
        i64 len = 1ll << i;
        i64 l   = (L + len - 1ll) / len;
        i64 r   = (R) / len;
        if (l < r) {
            st.insert(l * len);
            st.insert(r * len);
        } else {
            break;
        }
    }
    cout << (i64)st.size() - 1 << '\n';
    for (auto i = st.begin(); next(i) != st.end(); i++) {
        cout << *i << ' ' << *next(i) << '\n';
    }
    return 0;
}