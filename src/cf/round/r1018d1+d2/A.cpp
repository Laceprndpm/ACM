#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    int    l = 1, r = n;
    string cmd;
    cin >> cmd;
    deque<int> ans;
    for (auto it = cmd.rbegin(); it != cmd.rend(); it++) {
        if (*it == '>')
            ans.push_front(r--);
        else
            ans.push_front(l++);
    }
    ans.push_front(r);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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