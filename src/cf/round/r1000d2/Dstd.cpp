#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<ll> arr(n), brr(m);
        for (ll& i : arr)
            cin >> i;
        for (ll& i : brr)
            cin >> i;
        sort(begin(arr), end(arr));
        sort(begin(brr), end(brr));
        vector<ll> asum(n + 2), bsum(m + 2);
        for (int i = 1; i <= n; i++)
            asum[i] = asum[i - 1] + (arr[n - i] - arr[i - 1]);
        for (int i = 1; i <= m; i++)
            bsum[i] = bsum[i - 1] + (brr[m - i] - brr[i - 1]);
        vector<ll> ans{0};
        // maximize asum[ka]+bsum[kb]
        // s.t. ka+kb = x
        //      ka*2+kb <= n -> ka*2+(x-ka) <= n -> ka+x <= n   -> ka <= n-x
        //      ka+kb*2 <= m -> ka+2*(x-ka) <= m -> 2*x-ka <= m -> ka >= 2*x-m
        //      ka >= 0, x-ka >= 0
        for (int x = 1; 2 * x - m <= n - x; x++) {
            ll L = max(0, 2 * x - m), R = min(x, n - x);
            if (L > R)
                break;
            auto f = [&](int ka) {
                return asum[ka] + bsum[x - ka];
            };
            while (R - L > 3) {
                ll mL = (L * 2 + R) / 3, mR = (L + R * 2) / 3;
                if (f(mL) > f(mR))
                    R = mR;
                else
                    L = mL;
            }
            ll mans = 0;
            for (int i = L; i <= R; i++) {
                mans = max(mans, f(i));
            }
            ans.push_back(mans);
        }
        int kmax = (int)size(ans) - 1;
        cout << kmax << "\n";
        for (int i = 1; i <= kmax; i++)
            cout << ans[i] << " \n"[i == kmax];
    }
}