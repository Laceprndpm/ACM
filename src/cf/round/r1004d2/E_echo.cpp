#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int>   a(n);
    vector<int>   zero;
    map<int, int> cnt;
    map<int, int> pos;
    vector<int>   nozero;
    int           ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0)
            zero.push_back(i);
        else {
            cnt[a[i]]++;
            if (!pos.count(a[i])) pos[a[i]] = i;
            ans++;
            nozero.push_back(a[i]);
        }
    }
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    if (cnt.empty()) {
        cout << 1 << '\n';
        return;
    }
    // for (auto [x, y] : cnt)
    // {
    //     if (y >= 2)
    //     {
    //         minpos = min(minpos, pos[x]);
    //     }
    //     else
    //         break;
    // }
    int minpos = 1e18;
    int las    = 0;
    int anspos = -1e18;
    for (auto [a, b] : pos) {
        if (a - las != 1) break;
        if (cnt[a] >= 2) {
            if (pos[a] < minpos) {
                anspos = pos[a] - 1;
                minpos = min(minpos, pos[a]);
            }
        } else
            minpos = min(minpos, pos[a]);
        las = a;
    }
    // cout << anspos << ' ';
    if (anspos == -1e18) {
        if (!zero.empty())
            cout << ans + 1 << '\n';
        else
            cout << ans << '\n';
        return;
    }
    if (!zero.empty()) {
        if (zero[0] <= anspos) {
            cout << ans + 1 << '\n';
            return;
        }
    }
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--)
        solve();
}