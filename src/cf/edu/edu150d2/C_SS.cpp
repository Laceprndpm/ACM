// LUOGU_RID: 112633872
#include <bits/stdc++.h>
using namespace std;
string    s;
long long c[200000][5], cd[5] = {1, 10, 100, 1000, 10000}, cur[5];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false), cin.tie(0);
    int       T, n, i, j, lim;
    long long cans, mans, cc = 0;
    for (cin >> T; T > 0; T--) {
        cin >> s;
        n = s.length();
        for (i = 0; i < n; i++) {
            for (j = 0; j < 5; j++)
                c[i][j] = 0;
        }
        for (i = 0; i < 5; i++)
            cur[i] = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < s[i] - 'A'; j++) {
                c[i][j] = cur[j];
                cur[j]  = 0;
            }
            for (; j < 5; j++)
                c[i][j] = cur[j];
            cur[s[i] - 'A']++;
        }
        cans = 0;
        mans = 0;
        lim  = 0;
        for (i = n - 1; i > -1; i--) {
            if (s[i] - 'A' >= lim)
                cans += cd[s[i] - 'A'];
            else
                cans -= cd[s[i] - 'A'];
            for (j = 0; j < lim; j++)
                c[i][j] = 0;
            cc = 0;
            if (s[i] - 'A' >= lim)
                cc -= cd[s[i] - 'A'];
            else
                cc += cd[s[i] - 'A'];
            for (j = 0; j < s[i] - 'A'; j++)
                cc += cd[j] * c[i][j] * 2;
            for (j = 0; j < s[i] - 'A'; j++) {
                if (j > 0) cc -= cd[j - 1] * c[i][j - 1] * 2;
                if (j >= lim)
                    mans = max(mans, cc + cd[j]);
                else
                    mans = max(mans, cc - cd[j]);
            }
            cc = 0;
            if (s[i] - 'A' >= lim)
                cc -= cd[s[i] - 'A'];
            else
                cc += cd[s[i] - 'A'];
            for (j = s[i] - 'A' + 1; j < 5; j++) {
                if (j > 0) cc -= cd[j - 1] * c[i][j - 1] * 2;
                if (j >= lim)
                    mans = max(mans, cc + cd[j]);
                else
                    mans = max(mans, cc - cd[j]);
            }
            lim = max(lim, s[i] - 'A');
        }
        cout << cans + mans << '\n';
    }
    return 0;
}