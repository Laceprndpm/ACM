#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        int ai;
        cin >> ai;
        cnt[ai]++;
    }

    if (cnt[0] == 0) {
        cout << n << '\n';
        return;
    }

    int i = 0;
    // 连
    int k1 = 0;
    // 断
    int k2 = INT32_MAX;
    while (true) {
        // 如果在这里直接断，必须保证前面连续，且此处为0
        k2 = min(k1 + cnt[i], k2);
        if (cnt[i] == 0) {
            break;
        }
        // 也可以考虑这里由1断
        if (cnt[i] > 1)
            k2 = min(k1 + cnt[i] - 1, k2);
        else
            k2 = min(k1, k2);
        // 如果想连续，必须除去多余的
        k1 += cnt[i] - 1;
        i++;
    }
    cout << max(n - k1, n - k2) << '\n';
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