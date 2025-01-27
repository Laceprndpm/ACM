#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int N = 5e6 + 5;

int input[N];
int diff[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, p;
    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
        cin >> input[i];
    }
    for (int i = 1; i <= n; i++) {
        diff[i] = input[i] - input[i - 1];
    }
    for (int i = 1; i <= p; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        diff[x] += z;
        diff[y + 1] -= z;
    }
    int ans = INT32_MAX;
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        cur += diff[i];
        ans = min(cur, ans);
    }
    cout << ans;
    return 0;
}