#include <stack>
#define REMOVE_ME
#include <iostream>
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
    int q;
    cin >> q;
    stack<int> st;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            st.push(x);
        }
        if (op == 2) {
            if (st.empty()) {
                cout << 0 << '\n';
            } else {
                cout << st.top() << '\n';
                st.pop();
            }
        }
    }
    return 0;
}