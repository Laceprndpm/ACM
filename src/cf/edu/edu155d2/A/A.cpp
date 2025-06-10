#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    int w, e;
    cin >> w >> e;
    bool win = true;
    for (int i = 1; i < n; i++) {
        int tmpw, tmpe;
        cin >> tmpw >> tmpe;
        if (win && tmpw >= w && tmpe >= e) {
            win = false;
        }
    }
    if (win)
        cout << w << '\n';
    else {
        cout << -1 << '\n';
    }
}

signed main(int argc, char **argv)
{
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