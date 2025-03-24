#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t;

int num(int x)
{
    if (x == 0) return 1;
    return (int)(log10(x)) + 1;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>   a(n + 1), b(n + 1);
    map<int, int> mp, cut;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        mp[a[i]]++;
    }

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (mp.count(x) && mp[x] > 0) {
            mp[x]--;
            cut[x]++;
        } else {
            b[i] = x;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (cut.count(a[i]) && cut[a[i]] > 0) {
            cut[a[i]]--;
            a[i] = 0;
        }
    }

    vector<int> cnt_a(11, 0), cnt_b(11, 0);
    int         ans = 0;

    for (int i = 1; i <= n; ++i) {
        if (a[i] != 0 && a[i] != 1) {
            if (a[i] >= 10) {
                int digits = num(a[i]);
                ans++;
                cnt_a[digits]++;
            } else {
                cnt_a[a[i]]++;
            }
        }
        if (b[i] != 0 && b[i] != 1) {
            if (b[i] >= 10) {
                int digits = num(b[i]);
                ans++;
                cnt_b[digits]++;
            } else {
                cnt_b[b[i]]++;
            }
        }
    }

    for (int i = 2; i <= 10; ++i) {
        ans += abs(cnt_a[i] - cnt_b[i]);
    }

    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--)
        solve();
    return 0;
}