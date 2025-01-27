#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int cnt[1005];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int  n, m;
    bool dupi = false;
    cin >> n >> m;
    vector<int> input(n);

    set<int> s_set;
    for (int i = 0; i < n; i++) {
        cin >> input[i];
        if (s_set.find(input[i] % m) != s_set.end()) {
            dupi = true;
        }
        s_set.insert(input[i] % m);
    }
    if (dupi) {
        cout << 0 << '\n';
        return 0;
    }
    LL ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans *= abs(input[j] - input[i]);
            ans %= m;
        }
    }
    cout << ans;
    return 0;
}