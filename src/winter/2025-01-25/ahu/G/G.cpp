#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    set<int>      unique_size(a.begin(), a.end());
    map<int, int> r2v;
    {
        int i = 0;
        for (int iter : unique_size) {
            r2v[i] = iter;
            i++;
        }
    }
    map<int, int> v2r;
    for (auto iter : r2v) {
        v2r[iter.second] = iter.first;
    }
    vector<int> cnt_r(v2r.size(), 0);
    for (int i : a) {
        cnt_r[v2r[i]]++;
    }

    // 开始计算
    int ans   = 0;
    int cur_r = 0;
    while (cur_r < v2r.size()) {
        while (cnt_r[cur_r] != 0) {
            ans++;
            int i = cur_r;
            while (i < v2r.size()) {
                if (cnt_r[i] > 0)
                    cnt_r[i]--;
                else {
                    break;
                }

                if (r2v[i + 1] == r2v[i] + 1) {
                    i++;
                } else {
                    break;
                }
            }
        }
        cur_r++;
    }
    cout << ans << endl;
}

signed main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
