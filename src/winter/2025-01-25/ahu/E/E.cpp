#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int N = 2e5 + 5;
int           a[N];
int           b[N];

void solve(void) {
    int n;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    int       max_p = INT32_MIN;
    list<int> max_p_idx;
    for (int i = 1; i <= n; i++) {
        if (max_p < a[i] - b[i]) {
            max_p = a[i] - b[i];
            max_p_idx.clear();
            max_p_idx.push_back(i);
        } else if (max_p == a[i] - b[i]) {
            max_p_idx.push_back(i);
        }
    }
    cout << max_p_idx.size() << '\n';
    for (auto i : max_p_idx) {
        cout << i << ' ';
    }
    cout << '\n';
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