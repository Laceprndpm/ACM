#include <iostream>
#include <vector>

using namespace std;
constexpr int INF = 1e9;
// C
void solve()
{
    int n, x;
    cin >> n >> x;
    vector<int> ans;
    int         i;
    for (i = 0; i < n; i++) {
        if (i & ~x) break;
        ans.push_back(i);
    }
    for (; i < n; i++) {
        ans.push_back(x);
    }
    int or_val = 0;
    for (int i : ans) {
        or_val |= i;
    }
    if (or_val != x) {
        ans.back() = x;
    }
    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
