#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve(void) {

    int q;
    cin >> q;
    vector<int> dpMax(q + 10, INT32_MIN), dpMin(q + 10, INT32_MAX), maxN(q + 10, INT32_MIN), minN(q + 10, INT32_MAX);
    dpMax[1] = maxN[1] = 1;
    dpMin[1] = minN[1] = 0;
    int idx            = 1;
    for (int i = 1; i <= q; i++) {
        char command;
        cin >> command;
        if (command == '+') {
            int u, v;
            idx++;
            cin >> u >> v;
            dpMax[idx] = max(dpMax[u] + v, v);
            dpMin[idx] = min(dpMin[u] + v, v);
            maxN[idx]  = max(dpMax[idx], maxN[u]);
            minN[idx]  = min(dpMin[idx], minN[u]);
        } else {
            int u, v, w;
            cin >> u >> v >> w;
            cout << ((maxN[v] >= w && w >= minN[v]) ? "YES" : "NO");
            cout << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}