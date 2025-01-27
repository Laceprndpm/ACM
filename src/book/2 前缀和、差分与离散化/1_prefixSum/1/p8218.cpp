#include <bits/stdc++.h>
using namespace std;
using LL        = long long;
constexpr int N = 1e5 + 5;
LL            presum[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> presum[i];
        presum[i] += presum[i - 1];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        cout << presum[r] - presum[l - 1] << '\n';
    }
    return 0;
}