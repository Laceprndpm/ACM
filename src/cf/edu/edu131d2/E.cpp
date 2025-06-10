#include <bits/stdc++.h>

using namespace std;

vector<int> zf(const string &s)
{
    int         n = s.size();
    vector<int> z(n);
    int         l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        int    n, m;
        string s, t;
        cin >> n >> m >> s >> t;

        int ans = 1e9;

        bool        bad = false;
        vector<int> lpos(m), rpos(m);
        for (int i = 0; i < m; ++i) {
            if (i > 0) {
                lpos[i] = lpos[i - 1] + 1;
            } else {
                lpos[i] = 0;
            }
            while (lpos[i] < n && s[lpos[i]] != t[i]) {
                ++lpos[i];
            }
            if (lpos[i] >= n) {
                bad = true;
                break;
            }
        }
        for (int i = m - 1; i >= 0; --i) {
            if (i + 1 < m) {
                rpos[i] = rpos[i + 1] - 1;
            } else {
                rpos[i] = n - 1;
            }
            while (rpos[i] >= 0 && s[rpos[i]] != t[i]) {
                --rpos[i];
            }
            if (rpos[i] < 0) {
                bad = true;
                break;
            }
        }
        if (bad) {
            cout << -1 << endl;
            continue;
        }

        for (int pos = 0; pos <= n; ++pos) {
            string tmp = s.substr(0, pos);
            reverse(tmp.begin(), tmp.end());
            tmp += "#" + t;
            reverse(tmp.begin() + pos + 1, tmp.end());
            vector<int> z = zf(tmp);
            for (int suf = 0; suf <= m; ++suf) {
                if (pos - suf < 0) {
                    continue;
                }
                if (suf < m && rpos[suf] < pos) {
                    continue;
                }
                if (suf - 1 >= 0 && lpos[suf - 1] > pos) {
                    continue;
                }
                int rg = 0;
                if (suf != 0) {
                    int sum = (pos - z[pos + 1 + m - suf]) + (pos - suf);
                    rg      = (sum != 0) + sum;
                } else {
                    rg = pos;
                }
                ans = min(ans, (n - pos) + rg);
            }
        }
        cout << ans << endl;
    }

    return 0;
}