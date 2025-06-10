#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    vector<int> cnt(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int ai_input;
        cin >> ai_input;
        cnt[ai_input]++;
    }
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 1) {
            cout << "No" << '\n';
            return;
        }
        if (cnt[i] >= 2 && i != n) {
            cnt[i + 1] += cnt[i] - 2;
        }
    }
    cout << "Yes" << '\n';
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