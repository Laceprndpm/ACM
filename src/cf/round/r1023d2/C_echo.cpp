#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e17
#define pii pair<int, int>

void Echo2()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if (count(s.begin(), s.end(), '0') == 0) {
        int sum = 0;
        for (auto x : a) {
            sum += x;
        }
        if (sum != k) {
            cout << "NO" << '\n';
            return;
        } else {
            cout << "YES" << '\n';
            for (auto x : a) {
                cout << x << ' ';
            }
            cout << '\n';
            return;
        }
    }
    int totmx = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            int l   = i;
            int r   = i;
            int mx  = 0;
            int sum = 0;
            while (r <= n - 1 && s[r] == '1') {
                if (sum >= 0)
                    sum += a[r];
                else
                    sum = a[r];
                mx = max(mx, sum);
                r++;
            }
            totmx = max(totmx, mx);
            i     = r;
        }
    }
    if (totmx > k) {
        cout << "NO" << '\n';
        return;
    } else if (totmx == k) {
        cout << "YES" << '\n';
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                cout << -inf << ' ';
            } else {
                cout << a[i] << ' ';
            }
        }
        cout << '\n';
        return;
    }
    // cout << "XXX" << ' ';
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            int l      = i - 1;
            int r      = i + 1;
            int lsum   = 0;
            int rsum   = 0;
            int lmxsum = 0;
            int rmxsum = 0;
            while (l >= 0 && s[l] == '1') {
                lsum += a[l];
                // cout << l << ' ';
                l--;
                lmxsum = max(lmxsum, lsum);
            }
            // cout << lmxsum << ' ';
            while (r <= n - 1 && s[r] == '1') {
                rsum += a[r];
                r++;
                rmxsum = max(rmxsum, rsum);
            }
            // cout << rmxsum << ' ';
            a[i] = k - lmxsum - rmxsum;
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                if (s[j] == '0') a[j] = -inf;
            }
            int mxsum = 0, cur = 0;
            for (int j = 0; j < n; j++) {
                if (cur >= 0)
                    cur += a[j];
                else
                    cur = a[j];
                mxsum = max(mxsum, cur);
            }
            if (mxsum == k) {
                cout << "YES" << '\n';
                for (int j = 0; j < n; j++) {
                    cout << a[j] << ' ';
                }
                cout << '\n';
                return;
            }
        }
    }
    cout << "NO" << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--)
        Echo2();
}