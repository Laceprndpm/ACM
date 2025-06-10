#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    vector<int>   input(n);
    map<int, int> cnt;
    int           cnt0  = 0;
    int           frist = -1;
    for (int i = 0; i < n; i++) {
        cin >> input[i];
        if (input[i] == 0) {
            cnt0++;
            if (frist == -1) {
                frist = i;
            }
        }
    }
    if (cnt0 == 0) {
        cout << n << '\n';
        return;
    } else {
        if (frist == 0) {
            cout << n - cnt0 + 1 << '\n';
            return;
        } else {
            vector<int> prefix(n + 1);
            prefix[0] = INT32_MAX;
            for (int i = 1; i <= n; i++) {
                prefix[i] = min(prefix[i - 1], input[i - 1]);
            }
            for (int i = 0; i < n; i++) {
                cnt[input[i]]++;
            }
            int mex = 0;
            while (cnt[mex]) {
                mex++;
            }
            int  mn   = INT32_MAX;
            bool good = true;
            cnt[0]    = 1;
            for (int i = 0; i < n && good; i++) {
                if (--cnt[input[i]] == 0) {
                    mex = min(mex, input[i]);
                }
                mn = min(mn, input[i]);
                if (mex > mn)
                    good = false;
            }
            cout << n - cnt0 + good << '\n';
        }
    }
}

signed main(int argc, char** argv)
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