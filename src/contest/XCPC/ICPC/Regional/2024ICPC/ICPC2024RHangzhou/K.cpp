#include <bits/stdc++.h>

#include <set>
#include <utility>
#include <vector>
using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> permu(n * m);
    for (int i = 0; i < n * m; i++) {
        cin >> permu[i];
        permu[i]--;
        permu[i] /= m;
    }
    auto check = [&](int x) {
        if (x >= n * m) return true;
        if (x < m) return false;
        vector<int> cnt(n);
        for (int i = 0; i < x; i++) {
            cnt[permu[i]]++;
        }
        for (int i = 0; i < n; i++) {
            if (cnt[i] + k >= m) {
                return true;
            }
        }
        return false;
    };
    int ans = 0;
    for (int i = 20; i >= 0; i--) {
        if (!check((1 << i) + ans)) {
            ans += 1 << i;
        }
    }
    cout << ans + 1 << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}