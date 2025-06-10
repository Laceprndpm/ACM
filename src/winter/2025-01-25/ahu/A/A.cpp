#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve(void) {
    int n, m;
    cin >> n >> m;
    string input_s;
    cin >> input_s;
    vector<int> cnt_char(60, 0);
    for (int i = 0; i < n; i++) {
        if ('a' <= input_s[i] && input_s[i] <= 'z') {
            cnt_char[input_s[i] - 'a']++;
        } else {
            cnt_char[input_s[i] - 'A' + 26]++;
        }
    }
    int ans   = 0;
    int extra = 0;
    for (int i = 0; i < 26; i++) {
        int cnt_ans   = min(cnt_char[i], cnt_char[i + 26]);
        int cnt_extra = abs(cnt_char[i] - cnt_char[i + 26]) / 2;
        ans += cnt_ans;
        extra += cnt_extra;
    }
    ans += min(extra, m);
    cout << ans << '\n';
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