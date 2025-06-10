// By StarSilk
#include <bits/stdc++.h>
using namespace std;
string      s;
vector<int> vc, vd, vx;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T, n, i, a, b, ab, ba, remain, l, p, cntA, cntB, csum;
    for (cin >> T; T > 0; T--) {
        cin >> s >> a >> b >> ab >> ba;
        n    = s.length();
        cntA = 0;
        cntB = 0;
        for (i = 0; i < n; i++) {
            if (s[i] == 'A')
                cntA++;
            else
                cntB++;
        }
        if (cntA <= a && cntB <= b) {
            cout << "YES\n";
            continue;
        }

        remain = max(cntA - a, cntB - b);
        if (remain > ab + ba) {
            cout << "NO\n";
            continue;
        }

        cntA = max(remain - ba, 0);
        cntB = max(remain - ab, 0);
        l    = 1;
        p    = s[0] - 'A';
        for (i = 1; i < n; i++) {
            if (s[i] != s[i - 1])
                l++;
            else {
                if (l % 2 == 0) {
                    if (p == 0)
                        vc.push_back(l / 2);
                    else
                        vd.push_back(l / 2);
                } else
                    vx.push_back(l / 2);
                l = 1;
                p = s[i] - 'A';
            }
        }
        if (l % 2 == 0) {
            if (p == 0)
                vc.push_back(l / 2);
            else
                vd.push_back(l / 2);
        } else
            vx.push_back(l / 2);
        sort(vc.begin(), vc.end(), greater<int>());
        sort(vd.begin(), vd.end(), greater<int>());
        csum = 0;
        for (i = 0; i < vc.size(); i++)
            csum += vc[i];
        for (i = 0; i < vx.size(); i++)
            csum += vx[i];
        for (i = 0; i < vd.size(); i++)
            csum += vd[i];
        for (i = 0; i < vc.size(); i++)
            cntA = max(0, cntA - vc[i]);
        for (i = 0; i < vx.size(); i++)
            cntA = max(0, cntA - vx[i]);
        for (i = 0; i < vd.size(); i++) {
            if (cntA > 0)
                csum--;
            cntA = max(0, cntA - vd[i] + 1);
        }
        for (i = 0; i < vd.size(); i++)
            cntB = max(0, cntB - vd[i]);
        for (i = 0; i < vx.size(); i++)
            cntB = max(0, cntB - vx[i]);
        for (i = 0; i < vc.size(); i++) {
            if (cntB > 0)
                csum--;
            cntB = max(0, cntB - vc[i] + 1);
        }
        if (csum < remain)
            cout << "NO\n";
        else
            cout << "YES\n";
        vc.clear();
        vd.clear();
        vx.clear();
    }
    return 0;
}