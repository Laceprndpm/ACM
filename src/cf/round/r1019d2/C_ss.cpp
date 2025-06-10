#include <bits/stdc++.h>
using namespace std;
int a[200000], psum[200001];

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T, n, k, i, j, s, f0, f1, flag, pl, pr;
    for (cin >> T; T > 0; T--) {
        cin >> n >> k;
        for (i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] <= k)
                a[i] = 0;
            else
                a[i] = 1;
        }
        psum[0] = 0;
        for (i = 0; i < n; i++) {
            if (a[i] == 0)
                psum[i + 1] = psum[i] + 1;
            else
                psum[i + 1] = psum[i] - 1;
        }
        f1   = 0;
        f0   = 0;
        flag = 0;
        for (i = 1; i < n; i++) {
            if (psum[i] >= psum[0]) {
                if (f0) {
                    flag = 1;
                    break;
                } else {
                    if (psum[i] > psum[0] && f1) {
                        flag = 1;
                        break;
                    } else {
                        if (psum[i] > psum[0])
                            f1 = 1;
                        else
                            f0 = 1;
                    }
                }
            }
        }
        if (flag) {
            cout << "YES\n";
            continue;
        }
        f1   = 0;
        f0   = 0;
        flag = 0;
        for (i = n - 1; i > 0; i--) {
            if (psum[i] <= psum[n]) {
                if (f0) {
                    flag = 1;
                    break;
                } else {
                    if (psum[i] < psum[n] && f1) {
                        flag = 1;
                        break;
                    } else {
                        if (psum[i] < psum[n])
                            f1 = 1;
                        else
                            f0 = 1;
                    }
                }
            }
        }
        if (flag) {
            cout << "YES\n";
            continue;
        }
        pl = n + 1;
        pr = -1;
        for (i = 1; i < n; i++) {
            if (psum[i] >= psum[0]) {
                pl = i;
                break;
            }
        }
        for (i = n - 1; i > 0; i--) {
            if (psum[i] <= psum[n]) {
                pr = i;
                break;
            }
        }
        if (pl < pr)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}