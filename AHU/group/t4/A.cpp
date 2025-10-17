#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> ans(k + 1);
    for (int i = 1; i <= n; i++) {
        ans[2 * i - 1] = {i, i};
    }
    for (int i = 1; i <= n - 1; i++) {
        ans[2 * i] = {i, i + 1};
    }
    ans[2 * n] = {n, 1};
    for (int i = 1; i <= 2 * n; i++) cout << ans[i].first << ' ' << ans[i].second << '\n';
    int now = 2 * n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j || j == i + 1) continue;
            if (i == n && j == 1) continue;
            if (now == k) return 0;
            cout << i << ' ' << j << '\n';
            now++;
        }
    }
}