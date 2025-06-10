#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;
#define int long long

void solve()
{
    int n;
    cin >> n;
    set<LL>    ans;
    vector<LL> ai(n + 1);
    int        strangepoint = -1;
    for (int i = 1; i <= n; i++) {
        cin >> ai[i];
        if (ai[i] != 1 && ai[i] != -1) {
            strangepoint = i;
        }
    }

    if (strangepoint != -1) {
        LL curMax = 0;
        LL curMin = 0;
        LL ansMax = 0;
        LL ansMin = 0;
        for (int i = 1; i < strangepoint; i++) {
            curMax = max(curMax + ai[i], max(ai[i], 0LL));
            curMin = min(curMin + ai[i], min(ai[i], 0LL));
            ansMax = max(ansMax, curMax);
            ansMin = min(ansMin, curMin);
        }

        for (int j = curMin; j <= curMax; j++) {
            ans.insert(j + ai[strangepoint]);
        }

        LL RcurMax = 0;
        LL RcurMin = 0;
        for (int i = n; i > strangepoint; i--) {
            RcurMax = max(RcurMax + ai[i], max(ai[i], 0LL));
            RcurMin = min(RcurMin + ai[i], min(ai[i], 0LL));
            ansMax  = max(ansMax, RcurMax);
            ansMin  = min(ansMin, RcurMin);
        }

        for (int j = curMin + RcurMin; j <= curMax + RcurMax; j++) {
            ans.insert(j + ai[strangepoint]);
        }

        for (int i = ansMin; i <= ansMax; i++) {
            ans.insert(i);
        }

        cout << ans.size() << '\n';
        for (int iter : ans) {
            cout << iter << ' ';
        }
        cout << '\n';
    } else {
        LL curMax = 0;
        LL curMin = 0;
        LL ansMax = 0;
        LL ansMin = 0;
        for (int i = 1; i <= n; i++) {
            curMax = max(curMax + ai[i], max(ai[i], 0LL));
            curMin = min(curMin + ai[i], min(ai[i], 0LL));
            ansMax = max(ansMax, curMax);
            ansMin = min(ansMin, curMin);
        }
        cout << ansMax - ansMin + 1 << '\n';
        for (int i = ansMin; i <= ansMax; i++) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

signed main()
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