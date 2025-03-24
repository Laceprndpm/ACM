#include <bits/stdc++.h>
using namespace std;
long long l[200000], r[200000];

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int       T, n, i;
    long long k, minans, csum, cc, d, ck2, q;
    for (cin >> T; T > 0; T--) {
        cin >> n >> k;
        for (i = 0; i < n; i++)
            cin >> l[i];
        for (i = 0; i < n; i++)
            cin >> r[i];
        minans = 1000000000000000000LL;
        csum   = 0;
        cc     = 0;
        for (i = 0; i < n; i++) {
            csum += r[i] - l[i] + 1;
            if (csum < k) {
                if (r[i] == l[i]) cc++;
                continue;
            }
            d      = min(csum - k, cc);
            ck2    = k + d;
            q      = (i + 1) - d;
            minans = min(minans, max(l[i] - 1, r[i] - (csum - ck2)) + q * 2);
            if (r[i] == l[i]) cc++;
        }
        if (minans == 1000000000000000000LL)
            cout << "-1\n";
        else
            cout << minans << '\n';
    }
    return 0;
}